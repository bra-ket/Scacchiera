################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Bishop.cpp \
../Box.cpp \
../Chess.cpp \
../ChessBoard.cpp \
../Interface.cpp \
../King.cpp \
../Knight.cpp \
../Move.cpp \
../Pawn.cpp \
../Piece.cpp \
../Queen.cpp \
../Rook.cpp 

OBJS += \
./Bishop.o \
./Box.o \
./Chess.o \
./ChessBoard.o \
./Interface.o \
./King.o \
./Knight.o \
./Move.o \
./Pawn.o \
./Piece.o \
./Queen.o \
./Rook.o 

CPP_DEPS += \
./Bishop.d \
./Box.d \
./Chess.d \
./ChessBoard.d \
./Interface.d \
./King.d \
./Knight.d \
./Move.d \
./Pawn.d \
./Piece.d \
./Queen.d \
./Rook.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


