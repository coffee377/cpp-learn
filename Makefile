zip: check_file video
	@mkdir tmp -p
	@cp -r src docs CMakeLists.txt acm.bat README.jpg tmp -p
	@tar -zcvf acm.tar.gz -C tmp .
	@cd tmp && zip -r ../acm.zip . && cd ..
	@rm -rf tmp acm
check_file:
	@mkdir tmp -p
	@if [ -e "dist/acm.exe" ]; then \
  		cp dist/acm.exe tmp -p; \
    else \
        cp cmake-build-release/acm.exe tmp -p; \
    fi
video:
	@if [ -e "dist/acm.mp4" ]; then \
  		cp dist/acm.mp4 tmp -p; \
    fi