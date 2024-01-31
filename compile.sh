action=""

debug="debug"
release="release"
run="run"
run_binary="rbin"
clean="clean"
export_compile_commands="ecc"


echo "Possible actions:"
echo "  \"$debug\": build debug project version"
echo "  \"$release\": build release project version"
echo "  \"$run\": runs configured .app application"
echo "  \"$run_binary\": runs binary application"
echo "  \"$clean\": cleans project"
echo "  \"$export_compile_commands\": exports compile_commands.json for your clangd"

read -p "What do you want to do? " action

if [ $action = $debug ] ; then
  cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug && cmake --build build
  echo "The debug build has been compiled"

elif [ $action = $release ]; then
  cmake -B build -S . -DCMAKE_BUILD_TYPE=Release && cmake --build build
  echo "The release build has been compiled"

elif [ $action = $run ]; then
  open build/backuper.app

elif [ $action = $run_binary ]; then
  ./build/Backuper.app/Contents/MacOS/Backuper

elif [ $action = $clean ]; then
  rm -rf build
  rm compile_commands.json
  echo "Everything is cleaned up"

elif [ $action = $export_compile_commands ]; then
  mv build/compile_commands.json .

else
  echo "Wrong input"
fi