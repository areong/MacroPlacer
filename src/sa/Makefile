CC = g++
PATH_TO_SRC = ./../
INC = -I ${PATH_TO_SRC}

HEADERS_ANNEALINGSCHEDULE = \
	${PATH_TO_SRC}sa/AnnealingSchedule.h\
	${PATH_TO_SRC}sa/CostFunction.h\
	${PATH_TO_SRC}sa/Operation.h\
	${PATH_TO_SRC}sa/SimulatedAnnealing.h\
	${PATH_TO_SRC}sa/State.h

HEADERS_ANNEALINGSCHEDULERATIODECREASE = \
	${PATH_TO_SRC}sa/AnnealingSchedule.h\
	${PATH_TO_SRC}sa/AnnealingScheduleRatioDecrease.h

HEADERS_COSTFUNCTIONGROUP = \
	${PATH_TO_SRC}sa/CostFunction.h\
	${PATH_TO_SRC}sa/CostFunctionGroup.h\
	${PATH_TO_SRC}sa/Operation.h\
	${PATH_TO_SRC}sa/SimulatedAnnealing.h\
	${PATH_TO_SRC}sa/State.h

HEADERS_DECREASEVARIABLE = \
	${PATH_TO_SRC}sa/Operation.h\
	${PATH_TO_SRC}sa/DecreaseVariable.h\
	${PATH_TO_SRC}sa/Variable.h

HEADERS_INCREASEVARIABLE = \
	${PATH_TO_SRC}sa/Operation.h\
	${PATH_TO_SRC}sa/IncreaseVariable.h\
	${PATH_TO_SRC}sa/Variable.h

HEADERS_OPERATIONSET = \
	${PATH_TO_SRC}sa/Operation.h\
	${PATH_TO_SRC}sa/OperationSet.h\
	${PATH_TO_SRC}utils/Utils.h

HEADERS_POLYNOMIAL = \
	${PATH_TO_SRC}sa/CostFunction.h\
	${PATH_TO_SRC}sa/Polynomial.h\
	${PATH_TO_SRC}sa/Variable.h

HEADERS_SIMULATEDANNEALING = \
	${PATH_TO_SRC}sa/SimulatedAnnealing.h\
	${PATH_TO_SRC}sa/AnnealingSchedule.h\
	${PATH_TO_SRC}sa/CostFunction.h\
	${PATH_TO_SRC}sa/Operation.h\
	${PATH_TO_SRC}sa/State.h\
	${PATH_TO_SRC}sa/TemperatureListener.h\
	${PATH_TO_SRC}utils/Utils.h

HEADERS_SIMULATEDANNEALING_TEST = \
	${PATH_TO_SRC}sa/SimulatedAnnealing_test.h\
	${PATH_TO_SRC}sa/AnnealingScheduleRatioDecrease.h\
	${PATH_TO_SRC}sa/DecreaseVariable.h\
	${PATH_TO_SRC}sa/IncreaseVariable.h\
	${PATH_TO_SRC}sa/OperationSet.h\
	${PATH_TO_SRC}sa/Polynomial.h\
	${PATH_TO_SRC}sa/Variable.h\
	${PATH_TO_SRC}sa/SimulatedAnnealing.h

HEADERS_TEMPERATURELISTENER = \
	${PATH_TO_SRC}sa/TemperatureListener.h

HEADERS_VARIABLE = \
	${PATH_TO_SRC}sa/State.h\
	${PATH_TO_SRC}sa/Variable.h

all:
	make AnnealingSchedule.o
	make AnnealingScheduleRatioDecrease.o
	make CostFunctionGroup.o
	make DecreaseVariable.o
	make IncreaseVariable.o
	make OperationSet.o
	make Polynomial.o
	make SimulatedAnnealing.o
	make SimulatedAnnealing_test.o
	make TemperatureListener.o
	make Variable.o
AnnealingSchedule.o: AnnealingSchedule.cpp ${HEADERS_ANNEALINGSCHEDULE}
	${CC} -c AnnealingSchedule.cpp ${INC}
AnnealingScheduleRatioDecrease.o: AnnealingScheduleRatioDecrease.cpp ${HEADERS_ANNEALINGSCHEDULERATIODECREASE}
	${CC} -c AnnealingScheduleRatioDecrease.cpp ${INC}
CostFunctionGroup.o: CostFunctionGroup.cpp ${HEADERS_COSTFUNCTIONGROUP}
	${CC} -c CostFunctionGroup.cpp ${INC}
DecreaseVariable.o: DecreaseVariable.cpp ${HEADERS_DECREASEVARIABLE}
	${CC} -c DecreaseVariable.cpp ${INC}
IncreaseVariable.o: IncreaseVariable.cpp ${HEADERS_INCREASEVARIABLE}
	${CC} -c IncreaseVariable.cpp ${INC}
OperationSet.o: OperationSet.cpp ${HEADERS_OPERATIONSET}
	${CC} -c OperationSet.cpp ${INC}
Polynomial.o: Polynomial.cpp ${HEADERS_POLYNOMIAL}
	${CC} -c Polynomial.cpp ${INC}
SimulatedAnnealing.o: SimulatedAnnealing.cpp ${HEADERS_SIMULATEDANNEALING}
	${CC} -c SimulatedAnnealing.cpp ${INC}
SimulatedAnnealing_test.o: SimulatedAnnealing_test.cpp ${HEADERS_SIMULATEDANNEALING_TEST}
	${CC} -c SimulatedAnnealing_test.cpp ${INC}
TemperatureListener.o: TemperatureListener.cpp ${HEADERS_TEMPERATURELISTENER}
	${CC} -c TemperatureListener.cpp ${INC}
Variable.o: Variable.cpp ${HEADERS_VARIABLE}
	${CC} -c Variable.cpp ${INC}