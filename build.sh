# @Author: ksiric
# @Date:   2026-04-24 15:56:36
# @Last Modified by:   ksiric
# @Last Modified time: 2026-04-28 19:23:08

set -e

cmake -S . -B build
cmake --build build -j
python3 tools/dev/generate_clangd_compile_db.py
