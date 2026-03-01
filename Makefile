.PHONY: format

format:
	find . -type f \( -name "*.hpp" -o -name "*.cpp" \) -not -iwholename "*/.verify-helper/*" | xargs clang-format --Werror -i -style=file
