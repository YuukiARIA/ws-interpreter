main.o: main.cpp RuntimeException.h Label.h WSInput.h tree.h inst.h VM.h \
 Stack.h Heap.h
tree.o: tree.cpp tree.h
inst.o: inst.cpp inst.h
VM.o: VM.cpp VM.h inst.h Stack.h RuntimeException.h Heap.h
