CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++20 -O2 -Iinclude -Iimgui -Iimgui/backends
LDLLIBS := -lglfw -ldl -lGL


SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin
GLAD := include/glad.c
IMGUI_DIR := imgui
IMGUI_SRC := \
  $(IMGUI_DIR)/imgui.cpp \
	$(IMGUI_DIR)/imgui_draw.cpp\
	$(IMGUI_DIR)/imgui_tables.cpp\
	$(IMGUI_DIR)/imgui_widgets.cpp\
	$(IMGUI_DIR)/backends/imgui_impl_glfw.cpp \
	$(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

SRCS := $(shell find $(SRC_DIR) -name '*.cpp') $(GLAD) $(IMGUI_SRC)

OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

TARGET := $(BIN_DIR)/engine


all: $(TARGET)



$(TARGET):$(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDLLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/glad.o: $(GLAD)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(IMGUI_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -c $< -o $@



clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)


run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
