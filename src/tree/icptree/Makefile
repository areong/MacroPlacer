CC = g++
PATH_TO_SRC = ./../../
INC = -I ${PATH_TO_SRC}

HEADERS_ICPTREE = \
	${PATH_TO_SRC}tree/binarytree/BinaryTree.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}model/Macro.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h\
	${PATH_TO_SRC}tree/icptree/TraversalTaskPlaceNormalMacros.h\
	${PATH_TO_SRC}tree/icptree/TraversalTaskSetNotCovered.h\
	${PATH_TO_SRC}tree/icptree/contour/TopContour.h\
	${PATH_TO_SRC}tree/icptree/contour/BottomContour.h\
	${PATH_TO_SRC}tree/icptree/contour/RightContour.h\
	${PATH_TO_SRC}tree/icptree/contour/LeftContour.h\
	${PATH_TO_SRC}utils/Utils.h

HEADERS_ICPTREE_TEST = \
	${PATH_TO_SRC}tree/icptree/ICPTree_test.h\
	${PATH_TO_SRC}model/Macro.h\
	${PATH_TO_SRC}model/Floorplan.h\
	${PATH_TO_SRC}sa/AnnealingScheduleRatioDecrease.h\
	${PATH_TO_SRC}sa/CostFunctionGroup.h\
	${PATH_TO_SRC}sa/OperationSet.h\
	${PATH_TO_SRC}sa/SimulatedAnnealing.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h\
	${PATH_TO_SRC}tree/icptree/TraversalTaskPrintIdAndIdentity.h\
	${PATH_TO_SRC}tree/icptree/sa/AspectRatio.h\
	${PATH_TO_SRC}tree/icptree/sa/BoundingBoxArea.h\
	${PATH_TO_SRC}tree/icptree/sa/ChangeCorner0PositionRandomly.h\
	${PATH_TO_SRC}tree/icptree/sa/ChangeRandomEmptyNodeWidthRandomly.h\
	${PATH_TO_SRC}tree/icptree/sa/ChangeRandomMacroNodeVerticalDisplacementRandomly.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h\
	${PATH_TO_SRC}tree/icptree/sa/InsertEmptyNodeRandomly.h\
	${PATH_TO_SRC}tree/icptree/sa/InteriorRegionArea.h\
	${PATH_TO_SRC}tree/icptree/sa/MoveCornerRandomly.h\
	${PATH_TO_SRC}tree/icptree/sa/RefreshWindow.h\
	${PATH_TO_SRC}tree/icptree/sa/RemoveAndInsertLeftNodeRandomly.h\
	${PATH_TO_SRC}tree/icptree/sa/RemoveAndInsertRightNodeRandomly.h\
	${PATH_TO_SRC}tree/icptree/sa/RemoveEmptyNodeRandomly.h\
	${PATH_TO_SRC}tree/icptree/sa/SwapNodesRandomly.h\
	${PATH_TO_SRC}tree/icptree/sa/TotalWirelength.h\
	${PATH_TO_SRC}utils/Utils.h\
	${PATH_TO_SRC}view/FloorplanWindow.h

HEADERS_MACRONODE = \
	${PATH_TO_SRC}tree/binarytree/Node.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h\
	${PATH_TO_SRC}model/Macro.h\
	${PATH_TO_SRC}tree/binarytree/NextNodesBehaviorLeftFirst.h\
	${PATH_TO_SRC}tree/binarytree/NextNodesBehaviorRightFirst.h\
	${PATH_TO_SRC}tree/binarytree/NextNodesBehaviorRightOnly.h\
	${PATH_TO_SRC}tree/icptree/contour/Edge.h

HEADERS_TRAVERSALTASKPLACENORMALMACROS = \
	${PATH_TO_SRC}tree/binarytree/TraversalTask.h\
	${PATH_TO_SRC}tree/icptree/TraversalTaskPlaceNormalMacros.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h\
	${PATH_TO_SRC}tree/icptree/contour/Contour.h\
	${PATH_TO_SRC}tree/icptree/contour/Edge.h

HEADERS_TRAVERSALTASKPRINTIDANDIDENTITY = \
	${PATH_TO_SRC}tree/binarytree/TraversalTask.h\
	${PATH_TO_SRC}tree/icptree/TraversalTaskPrintIdAndIdentity.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h

HEADERS_TRAVERSALTASKSETNOTCOVERED = \
	${PATH_TO_SRC}tree/binarytree/TraversalTask.h\
	${PATH_TO_SRC}tree/icptree/TraversalTaskSetNotCovered.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h

all:
	make ICPTree.o
	make ICPTree_test.o
	make MacroNode.o
	make TraversalTaskPlaceNormalMacros.o
	make TraversalTaskPrintIdAndIdentity.o
	make TraversalTaskSetNotCovered.o
ICPTree.o: ICPTree.cpp ${HEADERS_ICPTREE}
	${CC} -c ICPTree.cpp ${INC}
ICPTree_test.o: ICPTree_test.cpp ${HEADERS_ICPTREE}
	${CC} -c ICPTree_test.cpp ${INC}
MacroNode.o: MacroNode.cpp ${HEADERS_MACRONODE}
	${CC} -c MacroNode.cpp ${INC}
TraversalTaskPlaceNormalMacros.o: TraversalTaskPlaceNormalMacros.cpp ${HEADERS_TRAVERSALTASKPLACENORMALMACROS}
	${CC} -c TraversalTaskPlaceNormalMacros.cpp ${INC}
TraversalTaskPrintIdAndIdentity.o: TraversalTaskPrintIdAndIdentity.cpp ${HEADERS_TRAVERSALTASKPRINTIDANDIDENTITY}
	${CC} -c TraversalTaskPrintIdAndIdentity.cpp ${INC}
TraversalTaskSetNotCovered.o: TraversalTaskSetNotCovered.cpp ${HEADERS_TRAVERSALTASKSETNOTCOVERED}
	${CC} -c TraversalTaskSetNotCovered.cpp ${INC}