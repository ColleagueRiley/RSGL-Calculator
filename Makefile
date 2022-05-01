all:
        echo run `make RSGL` to install RSGL
        echo run `make RSGLMake` to install RSGLMake

RSGL:
	git clone https://github.com/ColleagueRiley/RSGL.git
	cd RSGL && sudo make install
	rm -r RSGL

RSGLMake:
	git clone https://github.com/RSGL-org/RSGL-Make.git
	cd RSGL-Make && sudo make install
	sudo rm -r RSGL-Make