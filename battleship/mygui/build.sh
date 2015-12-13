export MYGUI_INSTALL="/home/julk/VIDEOJUEGOS/myguimaster/mygui-master"
export MYGUI_SOURCE_DIR="/home/julk/VIDEOJUEGOS/myguimaster/mygui-master"
make clean
make
mv tester ./bin
mv lib* ./bin
cp config/* ./bin


