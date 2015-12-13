export MYGUI_INSTALL="/home/julk/Downloads/myguimaster/mygui-master"
export MYGUI_SOURCE_DIR="/home/julk/Downloads/myguimaster/mygui-master"
make clean
make
mv tester ./bin
mv lib* ./bin
cp config/* ./bin
export MYGUI_SOURCE_DIR=/home/julk/Downloads/myguimaster/mygui-master


