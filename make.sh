#!/bin/bash


em++ js_api.cpp mini_board.cpp ultimate_board.cpp search.cpp -o js_api.js -O2 -s WASM=1 -std=c++11 -stdlib=libc++

rm js_api.js
python -m http.server 8000