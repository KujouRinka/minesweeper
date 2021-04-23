CC = g++
STD = -std=c++11
TmpDir = CMakeTmp
Src = src

Lib = $(TmpDir)/libcore.a $(TmpDir)/libdraw.a $(TmpDir)/libHistory.a
LibPar = -lcore -ldraw -lHistory
minesweeper : $(Lib) $(TmpDir)/main.o
	$(CC) $(STD) $(TmpDir)/main.o -o $@ -L./$(TmpDir) $(LibPar)

# main -------------------------------------------------------------
$(TmpDir)/main.o : $(Src)/main.cpp
	$(CC) $(STD) -c $< -o $@

# core -------------------------------------------------------------
CoreObj = $(TmpDir)/Controller/baseControl.o $(TmpDir)/Controller/UserOperation.o \
        $(TmpDir)/Controller/controllerOperation.o $(TmpDir)/MapGenerator/MapOperation.o \
        $(TmpDir)/MapGenerator/randomMine.o
$(TmpDir)/libcore.a : $(CoreObj)
	ar -rcs $(TmpDir)/libcore.a $(CoreObj)


# baseController ---------------------------------------------------

BCSrcPath = $(Src)/Controller
BCObjPath = $(TmpDir)/Controller

$(BCObjPath)/baseControl.o : $(BCSrcPath)/baseControl.cpp
	$(CC) $(STD) -c $< -o $@

$(BCObjPath)/UserOperation.o : $(BCSrcPath)/UserOperation.cpp
	$(CC) $(STD) -c $< -o $@

$(BCObjPath)/controllerOperation.o : $(BCSrcPath)/controllerOperation.cpp
	$(CC) $(STD) -c $< -o $@
# mapGenerator-----------------------
# NoProb
MGSrcPath = $(Src)/MapGenerator
MGSrc = $(MGSrcPath)/MapOperation.cpp $(MGSrcPath)/randomMine.cpp
MGObjPath = $(TmpDir)/MapGenerator
#MGObj = $(MGObjPath)/MapOperation.o $(MGObjPath)/randomMine.o
$(MGObjPath)/MapOperation.o : $(MGSrcPath)/MapOperation.cpp
	$(CC) $(STD) -c $< -o $@

$(MGObjPath)/randomMine.o : $(MGSrcPath)/randomMine.cpp
	$(CC) $(STD) -c $< -o $@


# draw --------------------------------------------------------------
# NoProb
DrawSrcPath = $(Src)/Controller
DrawSrc = $(DrawSrcPath)/drawDOS.c $(DrawSrcPath)/drawUNIX.c
DrawObjPath = $(TmpDir)/draw
DrawObj = $(DrawObjPath)/drawDOS.o $(DrawObjPath)/drawUNIX.o
$(TmpDir)/libdraw.a : $(DrawObj)
	ar -rcs $(TmpDir)/libdraw.a $(DrawObj)

$(DrawObjPath)/drawDOS.o : $(DrawSrcPath)/drawDOS.c
	$(CC) $(STD) -c $< -o $@

$(DrawObjPath)/drawUNIX.o : $(DrawSrcPath)/drawUNIX.c
	$(CC) $(STD) -c $< -o $@

# History -----------------------------------------------------------
# NoProb
HisSrcPath = $(Src)/History
HisSrc = $(HisSrcPath)/History.cpp
HisObjPath = $(TmpDir)/History
HisObj = $(HisObjPath)/History.o
$(TmpDir)/libHistory.a : $(HisObj)
	ar -rcs $@ $<

$(HisObjPath)/History.o : $(HisSrcPath)/History.cpp
	$(CC) $(STD) -c $< -o $@


# init --------------------------------------------------------------
.PHONY : init
init :
ifeq ($(OS),Windows_NT)
	-md CMakeTmp
	-md CMakeTmp\Controller
	-md CMakeTmp\draw
	-md CMakeTmp\History
	-md CMakeTmp\MapGenerator
endif

# clean -------------------------------------------------------------
.PHONY : clean
clean :
ifeq ($(OS),Windows_NT)
	-rd CMakeTmp /s/q
endif