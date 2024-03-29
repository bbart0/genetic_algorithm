cmake_minimum_required(VERSION 3.23)
project(miniProjektCLion)

set(CMAKE_CXX_STANDARD 14)

add_executable(miniProjektCLion main.cpp CKnapsackProblem.cpp CKnapsackProblem.h Item.cpp Item.h InvalidItem.h CIndividual.cpp CIndividual.h CGeneticAlgorithm.cpp CGeneticAlgorithm.h)
