CC = g++
PATH_TO_SRC = ./../../../
INC = -I ${PATH_TO_SRC}

HEADERS_ASPECTRATIO = \
	${PATH_TO_SRC}sa/CostFunction.h\
	${PATH_TO_SRC}tree/icptree/sa/AspectRatio.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h

HEADERS_BOUNDINGBOXAREA = \
	${PATH_TO_SRC}sa/CostFunction.h\
	${PATH_TO_SRC}tree/icptree/sa/BoundingBoxArea.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h

HEADERS_CHANGECORNER0POSITIONRANDOMLY = \
	${PATH_TO_SRC}sa/Operation.h\
	${PATH_TO_SRC}tree/icptree/sa/ChangeCorner0PositionRandomly.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h

HEADERS_CHANGERANDOMEMPTYNODEWIDTHRANDOMLY = \
	${PATH_TO_SRC}sa/Operation.h\
	${PATH_TO_SRC}tree/icptree/sa/ChangeRandomEmptyNodeWidthRandomly.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h

HEADERS_CHANGERANDOMMACRONODEVERTICALDISPLACEMENTRANDOMLY = \
	${PATH_TO_SRC}sa/Operation.h\
	${PATH_TO_SRC}tree/icptree/sa/ChangeRandomMacroNodeVerticalDisplacementRandomly.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h

HEADERS_FLOORPLANSTATE = \
	${PATH_TO_SRC}sa/State.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h\
	${PATH_TO_SRC}model/Floorplan.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h

HEADERS_INSERTEMPTYNODERANDOMLY = \
	${PATH_TO_SRC}sa/Operation.h\
	${PATH_TO_SRC}tree/icptree/sa/InsertEmptyNodeRandomly.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h

HEADERS_INTERIORREGIONAREA = \
	${PATH_TO_SRC}sa/CostFunction.h\
	${PATH_TO_SRC}tree/icptree/sa/InteriorRegionArea.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h

HEADERS_MOVECORNERRANDOMLY = \
	${PATH_TO_SRC}sa/Operation.h\
	${PATH_TO_SRC}tree/icptree/sa/MoveCornerRandomly.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h

HEADERS_REFRESHWINDOW = \
	${PATH_TO_SRC}sa/TemperatureListener.h\
	${PATH_TO_SRC}tree/icptree/sa/RefreshWindow.h\
	${PATH_TO_SRC}model/Floorplan.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h\
	${PATH_TO_SRC}sa/SimulatedAnnealing.h\
	${PATH_TO_SRC}view/Window.h

HEADERS_REMOVEANDINSERTLEFTNODERANDOMLY = \
	${PATH_TO_SRC}sa/Operation.h\
	${PATH_TO_SRC}tree/icptree/sa/RemoveAndInsertLeftNodeRandomly.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h

HEADERS_REMOVEANDINSERTRIGHTNODERANDOMLY = \
	${PATH_TO_SRC}sa/Operation.h\
	${PATH_TO_SRC}tree/icptree/sa/RemoveAndInsertRightNodeRandomly.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h

HEADERS_REMOVEEMPTYNODERANDOMLY = \
	${PATH_TO_SRC}sa/Operation.h\
	${PATH_TO_SRC}tree/icptree/sa/RemoveEmptyNodeRandomly.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h

HEADERS_SWAPNODESRANDOMLY = \
	${PATH_TO_SRC}sa/Operation.h\
	${PATH_TO_SRC}tree/icptree/sa/SwapNodesRandomly.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h

HEADERS_TOTALWIRELENGTH = \
	${PATH_TO_SRC}sa/CostFunction.h\
	${PATH_TO_SRC}tree/icptree/sa/TotalWirelength.h\
	${PATH_TO_SRC}model/Floorplan.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h

all:
	make AspectRatio.o
	make BoundingBoxArea.o
	make ChangeCorner0PositionRandomly.o
	make ChangeRandomEmptyNodeWidthRandomly.o
	make ChangeRandomMacroNodeVerticalDisplacementRandomly.o
	make FloorplanState.o
	make InsertEmptyNodeRandomly.o
	make InteriorRegionArea.o
	make MoveCornerRandomly.o
	make RefreshWindow.o
	make RemoveAndInsertLeftNodeRandomly.o
	make RemoveAndInsertRightNodeRandomly.o
	make RemoveEmptyNodeRandomly.o
	make SwapNodesRandomly.o
	make TotalWirelength.o
AspectRatio.o: AspectRatio.cpp ${HEADERS_ASPECTRATIO}
	${CC} -c AspectRatio.cpp ${INC}
BoundingBoxArea.o: BoundingBoxArea.cpp ${HEADERS_BOUNDINGBOXAREA}
	${CC} -c BoundingBoxArea.cpp ${INC}
ChangeCorner0PositionRandomly.o: ChangeCorner0PositionRandomly.cpp ${HEADERS_CHANGECORNER0POSITIONRANDOMLY}
	${CC} -c ChangeCorner0PositionRandomly.cpp ${INC}
ChangeRandomEmptyNodeWidthRandomly.o: ChangeRandomEmptyNodeWidthRandomly.cpp ${HEADERS_CHANGERANDOMEMPTYNODEWIDTHRANDOMLY}
	${CC} -c ChangeRandomEmptyNodeWidthRandomly.cpp ${INC}
ChangeRandomMacroNodeVerticalDisplacementRandomly.o: ChangeRandomMacroNodeVerticalDisplacementRandomly.cpp ${HEADERS_CHANGERANDOMMACRONODEVERTICALDISPLACEMENTRANDOMLY}
	${CC} -c ChangeRandomMacroNodeVerticalDisplacementRandomly.cpp ${INC}
FloorplanState.o: FloorplanState.cpp ${HEADERS_FLOORPLANSTATE}
	${CC} -c FloorplanState.cpp ${INC}
InsertEmptyNodeRandomly.o: InsertEmptyNodeRandomly.cpp ${HEADERS_INSERTEMPTYNODERANDOMLY}
	${CC} -c InsertEmptyNodeRandomly.cpp ${INC}
InteriorRegionArea.o: InteriorRegionArea.cpp ${HEADERS_INTERIORREGIONAREA}
	${CC} -c InteriorRegionArea.cpp ${INC}
MoveCornerRandomly.o: MoveCornerRandomly.cpp ${HEADERS_MOVECORNERRANDOMLY}
	${CC} -c MoveCornerRandomly.cpp ${INC}
RefreshWindow.o: RefreshWindow.cpp ${HEADERS_REFRESHWINDOW}
	${CC} -c RefreshWindow.cpp ${INC}
RemoveAndInsertLeftNodeRandomly.o: RemoveAndInsertLeftNodeRandomly.cpp ${HEADERS_REMOVEANDINSERTLEFTNODERANDOMLY}
	${CC} -c RemoveAndInsertLeftNodeRandomly.cpp ${INC}
RemoveAndInsertRightNodeRandomly.o: RemoveAndInsertRightNodeRandomly.cpp ${HEADERS_REMOVEANDINSERTRIGHTNODERANDOMLY}
	${CC} -c RemoveAndInsertRightNodeRandomly.cpp ${INC}
RemoveEmptyNodeRandomly.o: RemoveEmptyNodeRandomly.cpp ${HEADERS_REMOVEEMPTYNODERANDOMLY}
	${CC} -c RemoveEmptyNodeRandomly.cpp ${INC}
SwapNodesRandomly.o: SwapNodesRandomly.cpp ${HEADERS_SWAPNODESRANDOMLY}
	${CC} -c SwapNodesRandomly.cpp ${INC}
TotalWirelength.o: TotalWirelength.cpp ${HEADERS_TOTALWIRELENGTH}
	${CC} -c TotalWirelength.cpp ${INC}
clean:
	rm *.o