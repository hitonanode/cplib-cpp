---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/networksimplex.hpp
    title: "Network simplex method \uFF08\u30CD\u30C3\u30C8\u30EF\u30FC\u30AF\u5358\
      \u4F53\u6CD5\uFF0Cbased on LEMON\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B
  bundledCode: "#line 1 \"combinatorial_opt/test/mcf_ns.test.cpp\"\n#define PROBLEM\
    \ \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B\"\n#line\
    \ 2 \"combinatorial_opt/networksimplex.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <chrono>\n#include <cmath>\n#include <limits>\n#include <random>\n#include\
    \ <utility>\n#include <vector>\n\n// This program is the modificatiosn of the\n\
    // [lemon::NetworkSimplex](http://lemon.cs.elte.hu/pub/doc/latest-svn/a00404.html)\n\
    //\n/* -*- mode: C++; indent-tabs-mode: nil; -*-\n *\n * This file is a part of\
    \ LEMON, a generic C++ optimization library.\n *\n * Copyright (C) 2003-2013\n\
    \ * Egervary Jeno Kombinatorikus Optimalizalasi Kutatocsoport\n * (Egervary Research\
    \ Group on Combinatorial Optimization, EGRES).\n *\n * Permission to use, modify\
    \ and distribute this software is granted\n * provided that this copyright notice\
    \ appears in all copies. For\n * precise terms see the accompanying LICENSE file.\n\
    \ *\n * This software is provided \"AS IS\" with no warranty of any kind,\n *\
    \ express or implied, and with no claim as to its suitability for any\n * purpose.\n\
    \ *\n */\n\ntemplate <class Digraph, typename V = int, typename C = V> class NetworkSimplex\
    \ {\npublic:\n    using Node = int;\n    using Arc = int;\n    static const int\
    \ INVALID = -1;\n    typedef V Value; /// The type of the flow amounts, capacity\
    \ bounds and supply values\n    typedef C Cost;  /// The type of the arc costs\n\
    \npublic:\n    enum ProblemType { INFEASIBLE, OPTIMAL, UNBOUNDED };\n\n    ///\
    \ \\brief Constants for selecting the type of the supply constraints.\n    ///\n\
    \    /// Enum type containing constants for selecting the supply type,\n    ///\
    \ i.e. the direction of the inequalities in the supply/demand\n    /// constraints\
    \ of the \\ref min_cost_flow \"minimum cost flow problem\".\n    ///\n    ///\
    \ The default supply type is \\c GEQ, the \\c LEQ type can be\n    /// selected\
    \ using \\ref supplyType().\n    /// The equality form is a special case of both\
    \ supply types.\n    enum SupplyType {\n        /// This option means that there\
    \ are <em>\"greater or equal\"</em>\n        /// supply/demand constraints in\
    \ the definition of the problem.\n        GEQ,\n        /// This option means\
    \ that there are <em>\"less or equal\"</em>\n        /// supply/demand constraints\
    \ in the definition of the problem.\n        LEQ\n    };\n\n    /// \\brief Constants\
    \ for selecting the pivot rule.\n    ///\n    /// Enum type containing constants\
    \ for selecting the pivot rule for\n    /// the \\ref run() function.\n    ///\n\
    \    /// \\ref NetworkSimplex provides five different implementations for\n  \
    \  /// the pivot strategy that significantly affects the running time\n    ///\
    \ of the algorithm.\n    /// According to experimental tests conducted on various\
    \ problem\n    /// instances, \\ref BLOCK_SEARCH \"Block Search\" and\n    ///\
    \ \\ref ALTERING_LIST \"Altering Candidate List\" rules turned out\n    /// to\
    \ be the most efficient.\n    /// Since \\ref BLOCK_SEARCH \"Block Search\" is\
    \ a simpler strategy that\n    /// seemed to be slightly more robust, it is used\
    \ by default.\n    /// However, another pivot rule can easily be selected using\
    \ the\n    /// \\ref run() function with the proper parameter.\n    enum PivotRule\
    \ {\n\n        /// The \\e First \\e Eligible pivot rule.\n        /// The next\
    \ eligible arc is selected in a wraparound fashion\n        /// in every iteration.\n\
    \        FIRST_ELIGIBLE,\n\n        /// The \\e Best \\e Eligible pivot rule.\n\
    \        /// The best eligible arc is selected in every iteration.\n        BEST_ELIGIBLE,\n\
    \n        /// The \\e Block \\e Search pivot rule.\n        /// A specified number\
    \ of arcs are examined in every iteration\n        /// in a wraparound fashion\
    \ and the best eligible arc is selected\n        /// from this block.\n      \
    \  BLOCK_SEARCH,\n\n        /// The \\e Candidate \\e List pivot rule.\n     \
    \   /// In a major iteration a candidate list is built from eligible arcs\n  \
    \      /// in a wraparound fashion and in the following minor iterations\n   \
    \     /// the best eligible arc is selected from this list.\n        CANDIDATE_LIST,\n\
    \n        /// The \\e Altering \\e Candidate \\e List pivot rule.\n        ///\
    \ It is a modified version of the Candidate List method.\n        /// It keeps\
    \ only a few of the best eligible arcs from the former\n        /// candidate\
    \ list and extends this list in every iteration.\n        ALTERING_LIST\n    };\n\
    \nprivate:\n    using IntVector = std::vector<int>;\n    using ValueVector = std::vector<Value>;\n\
    \    using CostVector = std::vector<Cost>;\n    using CharVector = std::vector<signed\
    \ char>;\n    enum ArcState { STATE_UPPER = -1, STATE_TREE = 0, STATE_LOWER =\
    \ 1 };\n    enum ArcDirection { DIR_DOWN = -1, DIR_UP = 1 };\n\nprivate:\n   \
    \ // Data related to the underlying digraph\n    const Digraph &_graph;\n    int\
    \ _node_num;\n    int _arc_num;\n    int _all_arc_num;\n    int _search_arc_num;\n\
    \n    // Parameters of the problem\n    bool _has_lower;\n    SupplyType _stype;\n\
    \    Value _sum_supply;\n\n    // Data structures for storing the digraph\n  \
    \  IntVector _source;\n    IntVector _target;\n\n    // Node and arc data\n  \
    \  ValueVector _lower;\n    ValueVector _upper;\n    ValueVector _cap;\n    CostVector\
    \ _cost;\n    ValueVector _supply;\n    ValueVector _flow;\n    CostVector _pi;\n\
    \n    // Data for storing the spanning tree structure\n    IntVector _parent;\n\
    \    IntVector _pred;\n    IntVector _thread;\n    IntVector _rev_thread;\n  \
    \  IntVector _succ_num;\n    IntVector _last_succ;\n    CharVector _pred_dir;\n\
    \    CharVector _state;\n    IntVector _dirty_revs;\n    int _root;\n\n    //\
    \ Temporary data used in the current pivot iteration\n    int in_arc, join, u_in,\
    \ v_in, u_out, v_out;\n    Value delta;\n\n    const Value MAX;\n\npublic:\n \
    \   /// \\brief Constant for infinite upper bounds (capacities).\n    ///\n  \
    \  /// Constant for infinite upper bounds (capacities).\n    /// It is \\c std::numeric_limits<Value>::infinity()\
    \ if available,\n    /// \\c std::numeric_limits<Value>::max() otherwise.\n  \
    \  const Value INF;\n\nprivate:\n    // Implementation of the First Eligible pivot\
    \ rule\n    class FirstEligiblePivotRule {\n    private:\n        // References\
    \ to the NetworkSimplex class\n        const IntVector &_source;\n        const\
    \ IntVector &_target;\n        const CostVector &_cost;\n        const CharVector\
    \ &_state;\n        const CostVector &_pi;\n        int &_in_arc;\n        int\
    \ _search_arc_num;\n\n        // Pivot rule data\n        int _next_arc;\n\n \
    \   public:\n        // Constructor\n        FirstEligiblePivotRule(NetworkSimplex\
    \ &ns)\n            : _source(ns._source), _target(ns._target), _cost(ns._cost),\
    \ _state(ns._state),\n              _pi(ns._pi), _in_arc(ns.in_arc), _search_arc_num(ns._search_arc_num),\
    \ _next_arc(0) {}\n\n        // Find next entering arc\n        bool findEnteringArc()\
    \ {\n            Cost c;\n            for (int e = _next_arc; e != _search_arc_num;\
    \ ++e) {\n                c = _state[e] * (_cost[e] + _pi[_source[e]] - _pi[_target[e]]);\n\
    \                if (c < 0) {\n                    _in_arc = e;\n            \
    \        _next_arc = e + 1;\n                    return true;\n              \
    \  }\n            }\n            for (int e = 0; e != _next_arc; ++e) {\n    \
    \            c = _state[e] * (_cost[e] + _pi[_source[e]] - _pi[_target[e]]);\n\
    \                if (c < 0) {\n                    _in_arc = e;\n            \
    \        _next_arc = e + 1;\n                    return true;\n              \
    \  }\n            }\n            return false;\n        }\n\n    }; // class FirstEligiblePivotRule\n\
    \n    // Implementation of the Best Eligible pivot rule\n    class BestEligiblePivotRule\
    \ {\n    private:\n        // References to the NetworkSimplex class\n       \
    \ const IntVector &_source;\n        const IntVector &_target;\n        const\
    \ CostVector &_cost;\n        const CharVector &_state;\n        const CostVector\
    \ &_pi;\n        int &_in_arc;\n        int _search_arc_num;\n\n    public:\n\
    \        // Constructor\n        BestEligiblePivotRule(NetworkSimplex &ns)\n \
    \           : _source(ns._source), _target(ns._target), _cost(ns._cost), _state(ns._state),\n\
    \              _pi(ns._pi), _in_arc(ns.in_arc), _search_arc_num(ns._search_arc_num)\
    \ {}\n\n        // Find next entering arc\n        bool findEnteringArc() {\n\
    \            Cost c, min = 0;\n            for (int e = 0; e != _search_arc_num;\
    \ ++e) {\n                c = _state[e] * (_cost[e] + _pi[_source[e]] - _pi[_target[e]]);\n\
    \                if (c < min) {\n                    min = c;\n              \
    \      _in_arc = e;\n                }\n            }\n            return min\
    \ < 0;\n        }\n\n    }; // class BestEligiblePivotRule\n\n    // Implementation\
    \ of the Block Search pivot rule\n    class BlockSearchPivotRule {\n    private:\n\
    \        // References to the NetworkSimplex class\n        const IntVector &_source;\n\
    \        const IntVector &_target;\n        const CostVector &_cost;\n       \
    \ const CharVector &_state;\n        const CostVector &_pi;\n        int &_in_arc;\n\
    \        int _search_arc_num;\n\n        // Pivot rule data\n        int _block_size;\n\
    \        int _next_arc;\n\n    public:\n        // Constructor\n        BlockSearchPivotRule(NetworkSimplex\
    \ &ns)\n            : _source(ns._source), _target(ns._target), _cost(ns._cost),\
    \ _state(ns._state),\n              _pi(ns._pi), _in_arc(ns.in_arc), _search_arc_num(ns._search_arc_num),\
    \ _next_arc(0) {\n            // The main parameters of the pivot rule\n     \
    \       const double BLOCK_SIZE_FACTOR = 1.0;\n            const int MIN_BLOCK_SIZE\
    \ = 10;\n\n            _block_size = std::max(\n                int(BLOCK_SIZE_FACTOR\
    \ * std::sqrt(double(_search_arc_num))), MIN_BLOCK_SIZE);\n        }\n\n     \
    \   // Find next entering arc\n        bool findEnteringArc() {\n            Cost\
    \ c, min = 0;\n            int cnt = _block_size;\n            int e;\n      \
    \      for (e = _next_arc; e != _search_arc_num; ++e) {\n                c = _state[e]\
    \ * (_cost[e] + _pi[_source[e]] - _pi[_target[e]]);\n                if (c < min)\
    \ {\n                    min = c;\n                    _in_arc = e;\n        \
    \        }\n                if (--cnt == 0) {\n                    if (min < 0)\
    \ goto search_end;\n                    cnt = _block_size;\n                }\n\
    \            }\n            for (e = 0; e != _next_arc; ++e) {\n             \
    \   c = _state[e] * (_cost[e] + _pi[_source[e]] - _pi[_target[e]]);\n        \
    \        if (c < min) {\n                    min = c;\n                    _in_arc\
    \ = e;\n                }\n                if (--cnt == 0) {\n               \
    \     if (min < 0) goto search_end;\n                    cnt = _block_size;\n\
    \                }\n            }\n            if (min >= 0) return false;\n\n\
    \        search_end:\n            _next_arc = e;\n            return true;\n \
    \       }\n\n    }; // class BlockSearchPivotRule\n\n    // Implementation of\
    \ the Candidate List pivot rule\n    class CandidateListPivotRule {\n    private:\n\
    \        // References to the NetworkSimplex class\n        const IntVector &_source;\n\
    \        const IntVector &_target;\n        const CostVector &_cost;\n       \
    \ const CharVector &_state;\n        const CostVector &_pi;\n        int &_in_arc;\n\
    \        int _search_arc_num;\n\n        // Pivot rule data\n        IntVector\
    \ _candidates;\n        int _list_length, _minor_limit;\n        int _curr_length,\
    \ _minor_count;\n        int _next_arc;\n\n    public:\n        /// Constructor\n\
    \        CandidateListPivotRule(NetworkSimplex &ns)\n            : _source(ns._source),\
    \ _target(ns._target), _cost(ns._cost), _state(ns._state),\n              _pi(ns._pi),\
    \ _in_arc(ns.in_arc), _search_arc_num(ns._search_arc_num), _next_arc(0) {\n  \
    \          // The main parameters of the pivot rule\n            const double\
    \ LIST_LENGTH_FACTOR = 0.25;\n            const int MIN_LIST_LENGTH = 10;\n  \
    \          const double MINOR_LIMIT_FACTOR = 0.1;\n            const int MIN_MINOR_LIMIT\
    \ = 3;\n\n            _list_length = std::max(\n                int(LIST_LENGTH_FACTOR\
    \ * std::sqrt(double(_search_arc_num))), MIN_LIST_LENGTH);\n            _minor_limit\
    \ = std::max(int(MINOR_LIMIT_FACTOR * _list_length), MIN_MINOR_LIMIT);\n     \
    \       _curr_length = _minor_count = 0;\n            _candidates.resize(_list_length);\n\
    \        }\n\n        /// Find next entering arc\n        bool findEnteringArc()\
    \ {\n            Cost min, c;\n            int e;\n            if (_curr_length\
    \ > 0 && _minor_count < _minor_limit) {\n                // Minor iteration: select\
    \ the best eligible arc from the\n                // current candidate list\n\
    \                ++_minor_count;\n                min = 0;\n                for\
    \ (int i = 0; i < _curr_length; ++i) {\n                    e = _candidates[i];\n\
    \                    c = _state[e] * (_cost[e] + _pi[_source[e]] - _pi[_target[e]]);\n\
    \                    if (c < min) {\n                        min = c;\n      \
    \                  _in_arc = e;\n                    } else if (c >= 0) {\n  \
    \                      _candidates[i--] = _candidates[--_curr_length];\n     \
    \               }\n                }\n                if (min < 0) return true;\n\
    \            }\n\n            // Major iteration: build a new candidate list\n\
    \            min = 0;\n            _curr_length = 0;\n            for (e = _next_arc;\
    \ e != _search_arc_num; ++e) {\n                c = _state[e] * (_cost[e] + _pi[_source[e]]\
    \ - _pi[_target[e]]);\n                if (c < 0) {\n                    _candidates[_curr_length++]\
    \ = e;\n                    if (c < min) {\n                        min = c;\n\
    \                        _in_arc = e;\n                    }\n               \
    \     if (_curr_length == _list_length) goto search_end;\n                }\n\
    \            }\n            for (e = 0; e != _next_arc; ++e) {\n             \
    \   c = _state[e] * (_cost[e] + _pi[_source[e]] - _pi[_target[e]]);\n        \
    \        if (c < 0) {\n                    _candidates[_curr_length++] = e;\n\
    \                    if (c < min) {\n                        min = c;\n      \
    \                  _in_arc = e;\n                    }\n                    if\
    \ (_curr_length == _list_length) goto search_end;\n                }\n       \
    \     }\n            if (_curr_length == 0) return false;\n\n        search_end:\n\
    \            _minor_count = 1;\n            _next_arc = e;\n            return\
    \ true;\n        }\n\n    }; // class CandidateListPivotRule\n\n    // Implementation\
    \ of the Altering Candidate List pivot rule\n    class AlteringListPivotRule {\n\
    \    private:\n        // References to the NetworkSimplex class\n        const\
    \ IntVector &_source;\n        const IntVector &_target;\n        const CostVector\
    \ &_cost;\n        const CharVector &_state;\n        const CostVector &_pi;\n\
    \        int &_in_arc;\n        int _search_arc_num;\n\n        // Pivot rule\
    \ data\n        int _block_size, _head_length, _curr_length;\n        int _next_arc;\n\
    \        IntVector _candidates;\n        CostVector _cand_cost;\n\n        //\
    \ Functor class to compare arcs during sort of the candidate list\n        class\
    \ SortFunc {\n        private:\n            const CostVector &_map;\n\n      \
    \  public:\n            SortFunc(const CostVector &map) : _map(map) {}\n     \
    \       bool operator()(int left, int right) { return _map[left] < _map[right];\
    \ }\n        };\n\n        SortFunc _sort_func;\n\n    public:\n        // Constructor\n\
    \        AlteringListPivotRule(NetworkSimplex &ns)\n            : _source(ns._source),\
    \ _target(ns._target), _cost(ns._cost), _state(ns._state),\n              _pi(ns._pi),\
    \ _in_arc(ns.in_arc), _search_arc_num(ns._search_arc_num), _next_arc(0),\n   \
    \           _cand_cost(ns._search_arc_num), _sort_func(_cand_cost) {\n       \
    \     // The main parameters of the pivot rule\n            const double BLOCK_SIZE_FACTOR\
    \ = 1.0;\n            const int MIN_BLOCK_SIZE = 10;\n            const double\
    \ HEAD_LENGTH_FACTOR = 0.01;\n            const int MIN_HEAD_LENGTH = 3;\n\n \
    \           _block_size = std::max(\n                int(BLOCK_SIZE_FACTOR * std::sqrt(double(_search_arc_num))),\
    \ MIN_BLOCK_SIZE);\n            _head_length = std::max(int(HEAD_LENGTH_FACTOR\
    \ * _block_size), MIN_HEAD_LENGTH);\n            _candidates.resize(_head_length\
    \ + _block_size);\n            _curr_length = 0;\n        }\n\n        // Find\
    \ next entering arc\n        bool findEnteringArc() {\n            // Check the\
    \ current candidate list\n            int e;\n            Cost c;\n          \
    \  for (int i = 0; i != _curr_length; ++i) {\n                e = _candidates[i];\n\
    \                c = _state[e] * (_cost[e] + _pi[_source[e]] - _pi[_target[e]]);\n\
    \                if (c < 0) {\n                    _cand_cost[e] = c;\n      \
    \          } else {\n                    _candidates[i--] = _candidates[--_curr_length];\n\
    \                }\n            }\n\n            // Extend the list\n        \
    \    int cnt = _block_size;\n            int limit = _head_length;\n\n       \
    \     for (e = _next_arc; e != _search_arc_num; ++e) {\n                c = _state[e]\
    \ * (_cost[e] + _pi[_source[e]] - _pi[_target[e]]);\n                if (c < 0)\
    \ {\n                    _cand_cost[e] = c;\n                    _candidates[_curr_length++]\
    \ = e;\n                }\n                if (--cnt == 0) {\n               \
    \     if (_curr_length > limit) goto search_end;\n                    limit =\
    \ 0;\n                    cnt = _block_size;\n                }\n            }\n\
    \            for (e = 0; e != _next_arc; ++e) {\n                c = _state[e]\
    \ * (_cost[e] + _pi[_source[e]] - _pi[_target[e]]);\n                if (c < 0)\
    \ {\n                    _cand_cost[e] = c;\n                    _candidates[_curr_length++]\
    \ = e;\n                }\n                if (--cnt == 0) {\n               \
    \     if (_curr_length > limit) goto search_end;\n                    limit =\
    \ 0;\n                    cnt = _block_size;\n                }\n            }\n\
    \            if (_curr_length == 0) return false;\n\n        search_end:\n\n \
    \           // Perform partial sort operation on the candidate list\n        \
    \    int new_length = std::min(_head_length + 1, _curr_length);\n            std::partial_sort(_candidates.begin(),\
    \ _candidates.begin() + new_length,\n                              _candidates.begin()\
    \ + _curr_length, _sort_func);\n\n            // Select the entering arc and remove\
    \ it from the list\n            _in_arc = _candidates[0];\n            _next_arc\
    \ = e;\n            _candidates[0] = _candidates[new_length - 1];\n          \
    \  _curr_length = new_length - 1;\n            return true;\n        }\n\n   \
    \ }; // class AlteringListPivotRule\n\npublic:\n    NetworkSimplex(const Digraph\
    \ &graph)\n        : _graph(graph), MAX(std::numeric_limits<Value>::max()),\n\
    \          INF(std::numeric_limits<Value>::has_infinity ? std::numeric_limits<Value>::infinity()\n\
    \                                                       : MAX) {\n        // Check\
    \ the number types\n        static_assert(-Value(1) < 0, \"Value must be signed\"\
    );\n        static_assert(-Cost(1) < 0, \"Cost must be signed\");\n        static_assert(std::numeric_limits<Value>::max()\
    \ > 0, \"max() must be greater than 0\");\n\n        // Reset data structures\n\
    \        reset();\n    }\n\n    template <typename LowerMap> NetworkSimplex &lowerMap(const\
    \ LowerMap &map) {\n        _has_lower = true;\n        for (Arc a = 0; a < _arc_num;\
    \ a++) _lower[a] = map[a];\n        return *this;\n    }\n    template <typename\
    \ UpperMap> NetworkSimplex &upperMap(const UpperMap &map) {\n        for (Arc\
    \ a = 0; a < _arc_num; a++) _upper[a] = map[a];\n        return *this;\n    }\n\
    \    // Set costs of arcs (default value: 1)\n    template <typename CostMap>\
    \ NetworkSimplex &costMap(const CostMap &map) {\n        for (Arc a = 0; a < _arc_num;\
    \ a++) _cost[a] = map[a];\n        return *this;\n    }\n    template <typename\
    \ SupplyMap> NetworkSimplex &supplyMap(const SupplyMap &map) {\n        for (Node\
    \ n = 0; n < _node_num; n++) _supply[n] = map[n];\n        return *this;\n   \
    \ }\n    NetworkSimplex &stSupply(const Node &s, const Node &t, Value k) { //\
    \ set s-t flow\n        for (int i = 0; i != _node_num; ++i) _supply[i] = 0;\n\
    \        _supply[s] = k, _supply[t] = -k;\n        return *this;\n    }\n\n  \
    \  /// \\brief Set the type of the supply constraints.\n    ///\n    /// This\
    \ function sets the type of the supply/demand constraints.\n    /// If it is not\
    \ used before calling \\ref run(), the \\ref GEQ supply\n    /// type will be\
    \ used.\n    NetworkSimplex &supplyType(SupplyType supply_type) {\n        _stype\
    \ = supply_type;\n        return *this;\n    }\n\n    /// @}\n\n    /// This function\
    \ can be called more than once. All the given parameters\n    /// are kept for\
    \ the next call, unless \\ref resetParams() or \\ref reset()\n    /// is used,\
    \ thus only the modified parameters have to be set again.\n    /// If the underlying\
    \ digraph was also modified after the construction\n    /// of the class (or the\
    \ last \\ref reset() call), then the \\ref reset()\n    /// function must be called.\n\
    \    ProblemType run(PivotRule pivot_rule = BLOCK_SEARCH) {\n        if (!init())\
    \ return INFEASIBLE;\n        return start(pivot_rule);\n    }\n\n    /// \\brief\
    \ Reset all the parameters that have been given before.\n    ///\n    /// This\
    \ function resets all the paramaters that have been given\n    /// before using\
    \ functions \\ref lowerMap(), \\ref upperMap(),\n    /// \\ref costMap(), \\ref\
    \ supplyMap(), \\ref stSupply(), \\ref supplyType().\n    ///\n    /// It is useful\
    \ for multiple \\ref run() calls. Basically, all the given\n    /// parameters\
    \ are kept for the next \\ref run() call, unless\n    /// \\ref resetParams()\
    \ or \\ref reset() is used.\n    /// If the underlying digraph was also modified\
    \ after the construction\n    /// of the class or the last \\ref reset() call,\
    \ then the \\ref reset()\n    /// function must be used, otherwise \\ref resetParams()\
    \ is sufficient.\n    ///\n    /// For example,\n    /// \\code\n    ///   NetworkSimplex<ListDigraph>\
    \ ns(graph);\n    ///\n    ///   // First run\n    ///   ns.lowerMap(lower).upperMap(upper).costMap(cost)\n\
    \    ///     .supplyMap(sup).run();\n    ///\n    ///   // Run again with modified\
    \ cost map (resetParams() is not called,\n    ///   // so only the cost map have\
    \ to be set again)\n    ///   cost[e] += 100;\n    ///   ns.costMap(cost).run();\n\
    \    ///\n    ///   // Run again from scratch using resetParams()\n    ///   //\
    \ (the lower bounds will be set to zero on all arcs)\n    ///   ns.resetParams();\n\
    \    ///   ns.upperMap(capacity).costMap(cost)\n    ///     .supplyMap(sup).run();\n\
    \    /// \\endcode\n    ///\n    /// \\return <tt>(*this)</tt>\n    ///\n    ///\
    \ \\see reset(), run()\n    NetworkSimplex &resetParams() {\n        for (int\
    \ i = 0; i != _node_num; ++i) { _supply[i] = 0; }\n        for (int i = 0; i !=\
    \ _arc_num; ++i) {\n            _lower[i] = 0;\n            _upper[i] = INF;\n\
    \            _cost[i] = 1;\n        }\n        _has_lower = false;\n        _stype\
    \ = GEQ;\n        return *this;\n    }\n\n    /// \\brief Reset the internal data\
    \ structures and all the parameters\n    /// that have been given before.\n  \
    \  ///\n    /// This function resets the internal data structures and all the\n\
    \    /// paramaters that have been given before using functions \\ref lowerMap(),\n\
    \    /// \\ref upperMap(), \\ref costMap(), \\ref supplyMap(), \\ref stSupply(),\n\
    \    /// \\ref supplyType().\n    ///\n    /// It is useful for multiple \\ref\
    \ run() calls. Basically, all the given\n    /// parameters are kept for the next\
    \ \\ref run() call, unless\n    /// \\ref resetParams() or \\ref reset() is used.\n\
    \    /// If the underlying digraph was also modified after the construction\n\
    \    /// of the class or the last \\ref reset() call, then the \\ref reset()\n\
    \    /// function must be used, otherwise \\ref resetParams() is sufficient.\n\
    \    ///\n    /// See \\ref resetParams() for examples.\n    ///\n    /// \\return\
    \ <tt>(*this)</tt>\n    ///\n    /// \\see resetParams(), run()\n    NetworkSimplex\
    \ &reset() {\n        // Resize vectors\n        _node_num = _graph.countNodes();\n\
    \        _arc_num = _graph.countArcs();\n        int all_node_num = _node_num\
    \ + 1;\n        int max_arc_num = _arc_num + 2 * _node_num;\n\n        _source.resize(max_arc_num);\n\
    \        _target.resize(max_arc_num);\n\n        _lower.resize(_arc_num);\n  \
    \      _upper.resize(_arc_num);\n        _cap.resize(max_arc_num);\n        _cost.resize(max_arc_num);\n\
    \        _supply.resize(all_node_num);\n        _flow.resize(max_arc_num);\n \
    \       _pi.resize(all_node_num);\n\n        _parent.resize(all_node_num);\n \
    \       _pred.resize(all_node_num);\n        _pred_dir.resize(all_node_num);\n\
    \        _thread.resize(all_node_num);\n        _rev_thread.resize(all_node_num);\n\
    \        _succ_num.resize(all_node_num);\n        _last_succ.resize(all_node_num);\n\
    \        _state.resize(max_arc_num);\n\n        for (int a = 0; a < _arc_num;\
    \ ++a) {\n            _source[a] = _graph.source(a);\n            _target[a] =\
    \ _graph.target(a);\n        }\n        // Reset parameters\n        resetParams();\n\
    \        return *this;\n    }\n\n    /// @}\n\n    template <typename Number =\
    \ Cost> Number totalCost() const {\n        Number c = 0;\n        for (Arc a\
    \ = 0; a < _arc_num; a++) c += Number(_flow[a]) * Number(_cost[a]);\n        return\
    \ c;\n    }\n\n    Value flow(const Arc &a) const { return _flow[a]; }\n    template\
    \ <typename FlowMap> void flowMap(FlowMap &map) const {\n        for (Arc a =\
    \ 0; a < _arc_num; a++) { map.set(a, _flow[a]); }\n    }\n    ValueVector flowMap()\
    \ const { return _flow; }\n\n    Cost potential(const Node &n) const { return\
    \ _pi[n]; }\n    template <typename PotentialMap> void potentialMap(PotentialMap\
    \ &map) const {\n        for (int n = 0; n < _graph.V; n++) { map.set(n, _pi[n]);\
    \ }\n    }\n    CostVector potentialMap() const { return _pi; }\n\nprivate:\n\
    \    // Initialize internal data structures\n    bool init() {\n        if (_node_num\
    \ == 0) return false;\n\n        // Check the sum of supply values\n        _sum_supply\
    \ = 0;\n        for (int i = 0; i != _node_num; ++i) { _sum_supply += _supply[i];\
    \ }\n        if (!((_stype == GEQ && _sum_supply <= 0) || (_stype == LEQ && _sum_supply\
    \ >= 0)))\n            return false;\n\n        // Check lower and upper bounds\n\
    \        // LEMON_DEBUG(checkBoundMaps(), \"Upper bounds must be greater or equal\
    \ to the lower bounds\");\n\n        // Remove non-zero lower bounds\n       \
    \ if (_has_lower) {\n            for (int i = 0; i != _arc_num; ++i) {\n     \
    \           Value c = _lower[i];\n                if (c >= 0) {\n            \
    \        _cap[i] = _upper[i] < MAX ? _upper[i] - c : INF;\n                } else\
    \ {\n                    _cap[i] = _upper[i] < MAX + c ? _upper[i] - c : INF;\n\
    \                }\n                _supply[_source[i]] -= c;\n              \
    \  _supply[_target[i]] += c;\n            }\n        } else {\n            for\
    \ (int i = 0; i != _arc_num; ++i) { _cap[i] = _upper[i]; }\n        }\n\n    \
    \    // Initialize artifical cost\n        Cost ART_COST;\n        if (std::numeric_limits<Cost>::is_exact)\
    \ {\n            ART_COST = std::numeric_limits<Cost>::max() / 2 + 1;\n      \
    \  } else {\n            ART_COST = 0;\n            for (int i = 0; i != _arc_num;\
    \ ++i) {\n                if (_cost[i] > ART_COST) ART_COST = _cost[i];\n    \
    \        }\n            ART_COST = (ART_COST + 1) * _node_num;\n        }\n\n\
    \        // Initialize arc maps\n        for (int i = 0; i != _arc_num; ++i) {\n\
    \            _flow[i] = 0;\n            _state[i] = STATE_LOWER;\n        }\n\n\
    \        // Set data for the artificial root node\n        _root = _node_num;\n\
    \        _parent[_root] = -1;\n        _pred[_root] = -1;\n        _thread[_root]\
    \ = 0;\n        _rev_thread[0] = _root;\n        _succ_num[_root] = _node_num\
    \ + 1;\n        _last_succ[_root] = _root - 1;\n        _supply[_root] = -_sum_supply;\n\
    \        _pi[_root] = 0;\n\n        // Add artificial arcs and initialize the\
    \ spanning tree data structure\n        if (_sum_supply == 0) {\n            //\
    \ EQ supply constraints\n            _search_arc_num = _arc_num;\n           \
    \ _all_arc_num = _arc_num + _node_num;\n            for (int u = 0, e = _arc_num;\
    \ u != _node_num; ++u, ++e) {\n                _parent[u] = _root;\n         \
    \       _pred[u] = e;\n                _thread[u] = u + 1;\n                _rev_thread[u\
    \ + 1] = u;\n                _succ_num[u] = 1;\n                _last_succ[u]\
    \ = u;\n                _cap[e] = INF;\n                _state[e] = STATE_TREE;\n\
    \                if (_supply[u] >= 0) {\n                    _pred_dir[u] = DIR_UP;\n\
    \                    _pi[u] = 0;\n                    _source[e] = u;\n      \
    \              _target[e] = _root;\n                    _flow[e] = _supply[u];\n\
    \                    _cost[e] = 0;\n                } else {\n               \
    \     _pred_dir[u] = DIR_DOWN;\n                    _pi[u] = ART_COST;\n     \
    \               _source[e] = _root;\n                    _target[e] = u;\n   \
    \                 _flow[e] = -_supply[u];\n                    _cost[e] = ART_COST;\n\
    \                }\n            }\n        } else if (_sum_supply > 0) {\n   \
    \         // LEQ supply constraints\n            _search_arc_num = _arc_num +\
    \ _node_num;\n            int f = _arc_num + _node_num;\n            for (int\
    \ u = 0, e = _arc_num; u != _node_num; ++u, ++e) {\n                _parent[u]\
    \ = _root;\n                _thread[u] = u + 1;\n                _rev_thread[u\
    \ + 1] = u;\n                _succ_num[u] = 1;\n                _last_succ[u]\
    \ = u;\n                if (_supply[u] >= 0) {\n                    _pred_dir[u]\
    \ = DIR_UP;\n                    _pi[u] = 0;\n                    _pred[u] = e;\n\
    \                    _source[e] = u;\n                    _target[e] = _root;\n\
    \                    _cap[e] = INF;\n                    _flow[e] = _supply[u];\n\
    \                    _cost[e] = 0;\n                    _state[e] = STATE_TREE;\n\
    \                } else {\n                    _pred_dir[u] = DIR_DOWN;\n    \
    \                _pi[u] = ART_COST;\n                    _pred[u] = f;\n     \
    \               _source[f] = _root;\n                    _target[f] = u;\n   \
    \                 _cap[f] = INF;\n                    _flow[f] = -_supply[u];\n\
    \                    _cost[f] = ART_COST;\n                    _state[f] = STATE_TREE;\n\
    \                    _source[e] = u;\n                    _target[e] = _root;\n\
    \                    _cap[e] = INF;\n                    _flow[e] = 0;\n     \
    \               _cost[e] = 0;\n                    _state[e] = STATE_LOWER;\n\
    \                    ++f;\n                }\n            }\n            _all_arc_num\
    \ = f;\n        } else {\n            // GEQ supply constraints\n            _search_arc_num\
    \ = _arc_num + _node_num;\n            int f = _arc_num + _node_num;\n       \
    \     for (int u = 0, e = _arc_num; u != _node_num; ++u, ++e) {\n            \
    \    _parent[u] = _root;\n                _thread[u] = u + 1;\n              \
    \  _rev_thread[u + 1] = u;\n                _succ_num[u] = 1;\n              \
    \  _last_succ[u] = u;\n                if (_supply[u] <= 0) {\n              \
    \      _pred_dir[u] = DIR_DOWN;\n                    _pi[u] = 0;\n           \
    \         _pred[u] = e;\n                    _source[e] = _root;\n           \
    \         _target[e] = u;\n                    _cap[e] = INF;\n              \
    \      _flow[e] = -_supply[u];\n                    _cost[e] = 0;\n          \
    \          _state[e] = STATE_TREE;\n                } else {\n               \
    \     _pred_dir[u] = DIR_UP;\n                    _pi[u] = -ART_COST;\n      \
    \              _pred[u] = f;\n                    _source[f] = u;\n          \
    \          _target[f] = _root;\n                    _cap[f] = INF;\n         \
    \           _flow[f] = _supply[u];\n                    _state[f] = STATE_TREE;\n\
    \                    _cost[f] = ART_COST;\n                    _source[e] = _root;\n\
    \                    _target[e] = u;\n                    _cap[e] = INF;\n   \
    \                 _flow[e] = 0;\n                    _cost[e] = 0;\n         \
    \           _state[e] = STATE_LOWER;\n                    ++f;\n             \
    \   }\n            }\n            _all_arc_num = f;\n        }\n\n        return\
    \ true;\n    }\n\n    // Check if the upper bound is greater than or equal to\
    \ the lower bound\n    // on each arc.\n    bool checkBoundMaps() {\n        for\
    \ (int j = 0; j != _arc_num; ++j) {\n            if (_upper[j] < _lower[j]) return\
    \ false;\n        }\n        return true;\n    }\n\n    // Find the join node\n\
    \    void findJoinNode() {\n        int u = _source[in_arc];\n        int v =\
    \ _target[in_arc];\n        while (u != v) {\n            if (_succ_num[u] < _succ_num[v])\
    \ {\n                u = _parent[u];\n            } else {\n                v\
    \ = _parent[v];\n            }\n        }\n        join = u;\n    }\n\n    //\
    \ Find the leaving arc of the cycle and returns true if the\n    // leaving arc\
    \ is not the same as the entering arc\n    bool findLeavingArc() {\n        //\
    \ Initialize first and second nodes according to the direction\n        // of\
    \ the cycle\n        int first, second;\n        if (_state[in_arc] == STATE_LOWER)\
    \ {\n            first = _source[in_arc];\n            second = _target[in_arc];\n\
    \        } else {\n            first = _target[in_arc];\n            second =\
    \ _source[in_arc];\n        }\n        delta = _cap[in_arc];\n        int result\
    \ = 0;\n        Value c, d;\n        int e;\n\n        // Search the cycle form\
    \ the first node to the join node\n        for (int u = first; u != join; u =\
    \ _parent[u]) {\n            e = _pred[u];\n            d = _flow[e];\n      \
    \      if (_pred_dir[u] == DIR_DOWN) {\n                c = _cap[e];\n       \
    \         d = c >= MAX ? INF : c - d;\n            }\n            if (d < delta)\
    \ {\n                delta = d;\n                u_out = u;\n                result\
    \ = 1;\n            }\n        }\n\n        // Search the cycle form the second\
    \ node to the join node\n        for (int u = second; u != join; u = _parent[u])\
    \ {\n            e = _pred[u];\n            d = _flow[e];\n            if (_pred_dir[u]\
    \ == DIR_UP) {\n                c = _cap[e];\n                d = c >= MAX ? INF\
    \ : c - d;\n            }\n            if (d <= delta) {\n                delta\
    \ = d;\n                u_out = u;\n                result = 2;\n            }\n\
    \        }\n\n        if (result == 1) {\n            u_in = first;\n        \
    \    v_in = second;\n        } else {\n            u_in = second;\n          \
    \  v_in = first;\n        }\n        return result != 0;\n    }\n\n    // Change\
    \ _flow and _state vectors\n    void changeFlow(bool change) {\n        // Augment\
    \ along the cycle\n        if (delta > 0) {\n            Value val = _state[in_arc]\
    \ * delta;\n            _flow[in_arc] += val;\n            for (int u = _source[in_arc];\
    \ u != join; u = _parent[u]) {\n                _flow[_pred[u]] -= _pred_dir[u]\
    \ * val;\n            }\n            for (int u = _target[in_arc]; u != join;\
    \ u = _parent[u]) {\n                _flow[_pred[u]] += _pred_dir[u] * val;\n\
    \            }\n        }\n        // Update the state of the entering and leaving\
    \ arcs\n        if (change) {\n            _state[in_arc] = STATE_TREE;\n    \
    \        _state[_pred[u_out]] = (_flow[_pred[u_out]] == 0) ? STATE_LOWER : STATE_UPPER;\n\
    \        } else {\n            _state[in_arc] = -_state[in_arc];\n        }\n\
    \    }\n\n    // Update the tree structure\n    void updateTreeStructure() {\n\
    \        int old_rev_thread = _rev_thread[u_out];\n        int old_succ_num =\
    \ _succ_num[u_out];\n        int old_last_succ = _last_succ[u_out];\n        v_out\
    \ = _parent[u_out];\n\n        // Check if u_in and u_out coincide\n        if\
    \ (u_in == u_out) {\n            // Update _parent, _pred, _pred_dir\n       \
    \     _parent[u_in] = v_in;\n            _pred[u_in] = in_arc;\n            _pred_dir[u_in]\
    \ = u_in == _source[in_arc] ? DIR_UP : DIR_DOWN;\n\n            // Update _thread\
    \ and _rev_thread\n            if (_thread[v_in] != u_out) {\n               \
    \ int after = _thread[old_last_succ];\n                _thread[old_rev_thread]\
    \ = after;\n                _rev_thread[after] = old_rev_thread;\n           \
    \     after = _thread[v_in];\n                _thread[v_in] = u_out;\n       \
    \         _rev_thread[u_out] = v_in;\n                _thread[old_last_succ] =\
    \ after;\n                _rev_thread[after] = old_last_succ;\n            }\n\
    \        } else {\n            // Handle the case when old_rev_thread equals to\
    \ v_in\n            // (it also means that join and v_out coincide)\n        \
    \    int thread_continue = old_rev_thread == v_in ? _thread[old_last_succ] : _thread[v_in];\n\
    \n            // Update _thread and _parent along the stem nodes (i.e. the nodes\n\
    \            // between u_in and u_out, whose parent have to be changed)\n   \
    \         int stem = u_in;             // the current stem node\n            int\
    \ par_stem = v_in;         // the new parent of stem\n            int next_stem;\
    \               // the next stem node\n            int last = _last_succ[u_in];\
    \ // the last successor of stem\n            int before, after = _thread[last];\n\
    \            _thread[v_in] = u_in;\n            _dirty_revs.clear();\n       \
    \     _dirty_revs.push_back(v_in);\n            while (stem != u_out) {\n    \
    \            // Insert the next stem node into the thread list\n             \
    \   next_stem = _parent[stem];\n                _thread[last] = next_stem;\n \
    \               _dirty_revs.push_back(last);\n\n                // Remove the\
    \ subtree of stem from the thread list\n                before = _rev_thread[stem];\n\
    \                _thread[before] = after;\n                _rev_thread[after]\
    \ = before;\n\n                // Change the parent node and shift stem nodes\n\
    \                _parent[stem] = par_stem;\n                par_stem = stem;\n\
    \                stem = next_stem;\n\n                // Update last and after\n\
    \                last = _last_succ[stem] == _last_succ[par_stem] ? _rev_thread[par_stem]\n\
    \                                                                : _last_succ[stem];\n\
    \                after = _thread[last];\n            }\n            _parent[u_out]\
    \ = par_stem;\n            _thread[last] = thread_continue;\n            _rev_thread[thread_continue]\
    \ = last;\n            _last_succ[u_out] = last;\n\n            // Remove the\
    \ subtree of u_out from the thread list except for\n            // the case when\
    \ old_rev_thread equals to v_in\n            if (old_rev_thread != v_in) {\n \
    \               _thread[old_rev_thread] = after;\n                _rev_thread[after]\
    \ = old_rev_thread;\n            }\n\n            // Update _rev_thread using\
    \ the new _thread values\n            for (int i = 0; i != int(_dirty_revs.size());\
    \ ++i) {\n                int u = _dirty_revs[i];\n                _rev_thread[_thread[u]]\
    \ = u;\n            }\n\n            // Update _pred, _pred_dir, _last_succ and\
    \ _succ_num for the\n            // stem nodes from u_out to u_in\n          \
    \  int tmp_sc = 0, tmp_ls = _last_succ[u_out];\n            for (int u = u_out,\
    \ p = _parent[u]; u != u_in; u = p, p = _parent[u]) {\n                _pred[u]\
    \ = _pred[p];\n                _pred_dir[u] = -_pred_dir[p];\n               \
    \ tmp_sc += _succ_num[u] - _succ_num[p];\n                _succ_num[u] = tmp_sc;\n\
    \                _last_succ[p] = tmp_ls;\n            }\n            _pred[u_in]\
    \ = in_arc;\n            _pred_dir[u_in] = u_in == _source[in_arc] ? DIR_UP :\
    \ DIR_DOWN;\n            _succ_num[u_in] = old_succ_num;\n        }\n\n      \
    \  // Update _last_succ from v_in towards the root\n        int up_limit_out =\
    \ _last_succ[join] == v_in ? join : -1;\n        int last_succ_out = _last_succ[u_out];\n\
    \        for (int u = v_in; u != -1 && _last_succ[u] == v_in; u = _parent[u])\
    \ {\n            _last_succ[u] = last_succ_out;\n        }\n\n        // Update\
    \ _last_succ from v_out towards the root\n        if (join != old_rev_thread &&\
    \ v_in != old_rev_thread) {\n            for (int u = v_out; u != up_limit_out\
    \ && _last_succ[u] == old_last_succ; u = _parent[u]) {\n                _last_succ[u]\
    \ = old_rev_thread;\n            }\n        } else if (last_succ_out != old_last_succ)\
    \ {\n            for (int u = v_out; u != up_limit_out && _last_succ[u] == old_last_succ;\
    \ u = _parent[u]) {\n                _last_succ[u] = last_succ_out;\n        \
    \    }\n        }\n\n        // Update _succ_num from v_in to join\n        for\
    \ (int u = v_in; u != join; u = _parent[u]) { _succ_num[u] += old_succ_num; }\n\
    \        // Update _succ_num from v_out to join\n        for (int u = v_out; u\
    \ != join; u = _parent[u]) { _succ_num[u] -= old_succ_num; }\n    }\n\n    //\
    \ Update potentials in the subtree that has been moved\n    void updatePotential()\
    \ {\n        Cost sigma = _pi[v_in] - _pi[u_in] - _pred_dir[u_in] * _cost[in_arc];\n\
    \        int end = _thread[_last_succ[u_in]];\n        for (int u = u_in; u !=\
    \ end; u = _thread[u]) { _pi[u] += sigma; }\n    }\n\n    // Heuristic initial\
    \ pivots\n    bool initialPivots() {\n        Value curr, total = 0;\n       \
    \ std::vector<Node> supply_nodes, demand_nodes;\n        for (int u = 0; u < _node_num;\
    \ ++u) {\n            curr = _supply[u];\n            if (curr > 0) {\n      \
    \          total += curr;\n                supply_nodes.push_back(u);\n      \
    \      } else if (curr < 0) {\n                demand_nodes.push_back(u);\n  \
    \          }\n        }\n        if (_sum_supply > 0) total -= _sum_supply;\n\
    \        if (total <= 0) return true;\n\n        IntVector arc_vector;\n     \
    \   if (_sum_supply >= 0) {\n            if (supply_nodes.size() == 1 && demand_nodes.size()\
    \ == 1) {\n                // Perform a reverse graph search from the sink to\
    \ the source\n                std::vector<char> reached(_node_num, false);\n \
    \               Node s = supply_nodes[0], t = demand_nodes[0];\n             \
    \   std::vector<Node> stack;\n                reached[t] = true;\n           \
    \     stack.push_back(t);\n                while (!stack.empty()) {\n        \
    \            Node u, v = stack.back();\n                    stack.pop_back();\n\
    \                    if (v == s) break;\n                    // for (InArcIt a(_graph,\
    \ v); a != INVALID; ++a) {\n                    for (auto a : _graph.in_eids[v])\
    \ {\n                        if (reached[u = _graph.source(a)]) continue;\n  \
    \                      int j = a;\n                        if (_cap[j] >= total)\
    \ {\n                            arc_vector.push_back(j);\n                  \
    \          reached[u] = true;\n                            stack.push_back(u);\n\
    \                        }\n                    }\n                }\n       \
    \     } else {\n                // Find the min. cost incoming arc for each demand\
    \ node\n                for (int i = 0; i != int(demand_nodes.size()); ++i) {\n\
    \                    Node v = demand_nodes[i];\n                    Cost c, min_cost\
    \ = std::numeric_limits<Cost>::max();\n                    Arc min_arc = INVALID;\n\
    \                    for (auto a : _graph.in_eids[v]) {\n                    \
    \    // for (InArcIt a(_graph, v); a != INVALID; ++a) {\n                    \
    \    c = _cost[a];\n                        if (c < min_cost) {\n            \
    \                min_cost = c;\n                            min_arc = a;\n   \
    \                     }\n                    }\n                    if (min_arc\
    \ != INVALID) { arc_vector.push_back(min_arc); }\n                }\n        \
    \    }\n        } else {\n            // Find the min. cost outgoing arc for each\
    \ supply node\n            for (Node u : supply_nodes) {\n                Cost\
    \ c, min_cost = std::numeric_limits<Cost>::max();\n                Arc min_arc\
    \ = INVALID;\n                for (auto a : _graph.out_eids[u]) {\n          \
    \          c = _cost[a];\n                    if (c < min_cost) {\n          \
    \              min_cost = c;\n                        min_arc = a;\n         \
    \           }\n                }\n                if (min_arc != INVALID) { arc_vector.push_back(min_arc);\
    \ }\n            }\n        }\n\n        // Perform heuristic initial pivots\n\
    \        for (int i = 0; i != int(arc_vector.size()); ++i) {\n            in_arc\
    \ = arc_vector[i];\n            if (_state[in_arc] * (_cost[in_arc] + _pi[_source[in_arc]]\
    \ - _pi[_target[in_arc]]) >= 0)\n                continue;\n            findJoinNode();\n\
    \            bool change = findLeavingArc();\n            if (delta >= MAX) return\
    \ false;\n            changeFlow(change);\n            if (change) {\n       \
    \         updateTreeStructure();\n                updatePotential();\n       \
    \     }\n        }\n        return true;\n    }\n\n    // Execute the algorithm\n\
    \    ProblemType start(PivotRule pivot_rule) {\n        // Select the pivot rule\
    \ implementation\n        switch (pivot_rule) {\n        case FIRST_ELIGIBLE:\
    \ return start<FirstEligiblePivotRule>();\n        case BEST_ELIGIBLE: return\
    \ start<BestEligiblePivotRule>();\n        case BLOCK_SEARCH: return start<BlockSearchPivotRule>();\n\
    \        case CANDIDATE_LIST: return start<CandidateListPivotRule>();\n      \
    \  case ALTERING_LIST: return start<AlteringListPivotRule>();\n        }\n   \
    \     return INFEASIBLE; // avoid warning\n    }\n\n    template <typename PivotRuleImpl>\
    \ ProblemType start() {\n        PivotRuleImpl pivot(*this);\n\n        // Perform\
    \ heuristic initial pivots\n        if (!initialPivots()) return UNBOUNDED;\n\n\
    \        // Execute the Network Simplex algorithm\n        while (pivot.findEnteringArc())\
    \ {\n            findJoinNode();\n            bool change = findLeavingArc();\n\
    \            if (delta >= MAX) return UNBOUNDED;\n            changeFlow(change);\n\
    \            if (change) {\n                updateTreeStructure();\n         \
    \       updatePotential();\n            }\n        }\n\n        // Check feasibility\n\
    \        for (int e = _search_arc_num; e != _all_arc_num; ++e) {\n           \
    \ if (_flow[e] != 0) return INFEASIBLE;\n        }\n\n        // Transform the\
    \ solution and the supply map to the original form\n        if (_has_lower) {\n\
    \            for (int i = 0; i != _arc_num; ++i) {\n                Value c =\
    \ _lower[i];\n                if (c != 0) {\n                    _flow[i] += c;\n\
    \                    _supply[_source[i]] += c;\n                    _supply[_target[i]]\
    \ -= c;\n                }\n            }\n        }\n\n        // Shift potentials\
    \ to meet the requirements of the GEQ/LEQ type\n        // optimality conditions\n\
    \        if (_sum_supply == 0) {\n            if (_stype == GEQ) {\n         \
    \       Cost max_pot = -std::numeric_limits<Cost>::max();\n                for\
    \ (int i = 0; i != _node_num; ++i) {\n                    if (_pi[i] > max_pot)\
    \ max_pot = _pi[i];\n                }\n                if (max_pot > 0) {\n \
    \                   for (int i = 0; i != _node_num; ++i) _pi[i] -= max_pot;\n\
    \                }\n            } else {\n                Cost min_pot = std::numeric_limits<Cost>::max();\n\
    \                for (int i = 0; i != _node_num; ++i) {\n                    if\
    \ (_pi[i] < min_pot) min_pot = _pi[i];\n                }\n                if\
    \ (min_pot < 0) {\n                    for (int i = 0; i != _node_num; ++i) _pi[i]\
    \ -= min_pot;\n                }\n            }\n        }\n\n        return OPTIMAL;\n\
    \    }\n}; // class NetworkSimplex\n\ntemplate <typename Capacity = long long,\
    \ typename Weight = long long> struct mcf_graph_ns {\n\n    struct Digraph {\n\
    \        const int V;\n        int E;\n        std::vector<std::vector<int>> in_eids,\
    \ out_eids;\n        std::vector<std::pair<int, int>> arcs;\n        Digraph(int\
    \ V = 0) : V(V), E(0), in_eids(V), out_eids(V){};\n        int add_edge(int s,\
    \ int t) {\n            assert(0 <= s and s < V);\n            assert(0 <= t and\
    \ t < V);\n            in_eids[t].push_back(E), out_eids[s].push_back(E), arcs.emplace_back(s,\
    \ t), E++;\n            return E - 1;\n        }\n        int countNodes() const\
    \ noexcept { return V; }\n        int countArcs() const noexcept { return E; }\n\
    \        int source(int arcid) const { return arcs[arcid].first; }\n        int\
    \ target(int arcid) const { return arcs[arcid].second; }\n    };\n\n    struct\
    \ edge {\n        int eid;\n        int from, to;\n        Capacity lo, hi;\n\
    \        Weight weight;\n    };\n\n    int n;\n    std::vector<Capacity> bs;\n\
    \    bool infeasible;\n    std::vector<edge> Edges;\n\n    mcf_graph_ns(int V\
    \ = 0) : n(V), bs(V), infeasible(false) {}\n\n    int add_edge(int from, int to,\
    \ Capacity lower, Capacity upper, Weight weight) {\n        assert(from >= 0 and\
    \ from < n);\n        assert(to >= 0 and to < n);\n        int idnow = Edges.size();\n\
    \        Edges.push_back({idnow, from, to, lower, upper, weight});\n        return\
    \ idnow;\n    }\n    void add_supply(int v, Capacity b) {\n        assert(v >=\
    \ 0 and v < n);\n        bs[v] += b;\n    }\n    std::vector<Capacity> flow;\n\
    \    std::vector<Capacity> potential;\n\n    template <typename RetVal = __int128>\
    \ [[nodiscard]] RetVal solve() {\n        std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \n        std::vector<int> vid(n), eid(Edges.size());\n        std::iota(vid.begin(),\
    \ vid.end(), 0);\n        std::shuffle(vid.begin(), vid.end(), rng);\n       \
    \ std::iota(eid.begin(), eid.end(), 0);\n        std::shuffle(eid.begin(), eid.end(),\
    \ rng);\n\n        flow.clear();\n        potential.clear();\n        Digraph\
    \ graph(n + 1);\n\n        std::vector<Capacity> supplies(graph.countNodes());\n\
    \        std::vector<Capacity> lowers(Edges.size());\n        std::vector<Capacity>\
    \ uppers(Edges.size());\n        std::vector<Weight> weights(Edges.size());\n\n\
    \        for (int i = 0; i < n; i++) supplies[vid[i]] = bs[i];\n        for (auto\
    \ i : eid) {\n            const auto &e = Edges[i];\n            int arc = graph.add_edge(vid[e.from],\
    \ vid[e.to]);\n            lowers[arc] = e.lo;\n            uppers[arc] = e.hi;\n\
    \            weights[arc] = e.weight;\n        }\n\n        NetworkSimplex<Digraph,\
    \ Capacity, Weight> ns(graph);\n        auto status = ns.supplyMap(supplies).costMap(weights).lowerMap(lowers).upperMap(uppers).run(\n\
    \            decltype(ns)::BLOCK_SEARCH);\n\n        if (status == decltype(ns)::INFEASIBLE)\
    \ {\n            return infeasible = true, 0;\n        } else {\n            flow.resize(Edges.size());\n\
    \            potential.resize(n);\n            for (int i = 0; i < int(Edges.size());\
    \ i++) flow[eid[i]] = ns.flow(i);\n            for (int i = 0; i < n; i++) potential[i]\
    \ = ns.potential(vid[i]);\n            return ns.template totalCost<RetVal>();\n\
    \        }\n    }\n};\n#line 3 \"combinatorial_opt/test/mcf_ns.test.cpp\"\n#include\
    \ <iostream>\nusing namespace std;\n\nint main() {\n    int V, E, F;\n    cin\
    \ >> V >> E >> F;\n    mcf_graph_ns<int, int> mcf(V);\n    while (E--) {\n   \
    \     int u, v, c, d;\n        cin >> u >> v >> c >> d;\n        mcf.add_edge(u,\
    \ v, 0, c, d);\n    }\n\n    mcf.add_supply(0, F), mcf.add_supply(V - 1, -F);\n\
    \    auto ret = mcf.solve<int>();\n    cout << (mcf.infeasible ? -1 : ret) <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B\"\
    \n#include \"../networksimplex.hpp\"\n#include <iostream>\nusing namespace std;\n\
    \nint main() {\n    int V, E, F;\n    cin >> V >> E >> F;\n    mcf_graph_ns<int,\
    \ int> mcf(V);\n    while (E--) {\n        int u, v, c, d;\n        cin >> u >>\
    \ v >> c >> d;\n        mcf.add_edge(u, v, 0, c, d);\n    }\n\n    mcf.add_supply(0,\
    \ F), mcf.add_supply(V - 1, -F);\n    auto ret = mcf.solve<int>();\n    cout <<\
    \ (mcf.infeasible ? -1 : ret) << '\\n';\n}\n"
  dependsOn:
  - combinatorial_opt/networksimplex.hpp
  isVerificationFile: true
  path: combinatorial_opt/test/mcf_ns.test.cpp
  requiredBy: []
  timestamp: '2022-05-01 12:19:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorial_opt/test/mcf_ns.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/mcf_ns.test.cpp
- /verify/combinatorial_opt/test/mcf_ns.test.cpp.html
title: combinatorial_opt/test/mcf_ns.test.cpp
---
