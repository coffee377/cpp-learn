zip: check_file
	@rm -rf tmp acm
	@mkdir tmp -p
	@cp -r src docs CMakeLists.txt acm.bat README.jpg tmp -p
	@tar -zcvf acm.tar.gz -C tmp .
	@cd tmp && zip -r ../acm.zip . && cd ..
check_file:
	@mkdir tmp -p
	@if [ -e "dist/acm.exe" ]; then \
  		cp dist/acm.exe tmp -p; \
    else \
        cp cmake-build-release/acm.exe tmp -p; \
    fi