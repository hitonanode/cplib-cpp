.PHONY: format

format:
	find . -name "*.hpp" -o -name "*.cpp" -not -iwholename "*/.verify-helper/*" | xargs clang-format --Werror -i -style=file
