#ifndef WINDOW_CONSTANTS_HPP
#define WINDOW_CONSTANTS_HPP

// Scene Window Size
constexpr int SCENE_WIN_W = 600;
constexpr int SCENE_WIN_H = 600;

// Hierarchy Panel
constexpr int HIERARCHY_PANEL_W = 200; // Hiearchy panel width
constexpr int HIERARCHY_PANEL_H = SCENE_WIN_W;

// Inspector Panel
constexpr int INSPECTOR_PANEL_W = 200; // Inspector panel width
constexpr int INSPECTOR_PANEL_H = SCENE_WIN_H;

// Object Panel
constexpr int OBJECTS_PANEL_W = HIERARCHY_PANEL_W + SCENE_WIN_W + INSPECTOR_PANEL_W; // Height of the bottom panel
constexpr int OBJECTS_PANEL_H = 200; // Height of the bottom panel

// Top Panel
constexpr int TOP_PANEL_W = HIERARCHY_PANEL_W + SCENE_WIN_W + INSPECTOR_PANEL_W;
constexpr int TOP_PANEL_H = 50; // Height of top panel

// Window Position
constexpr int ENGINE_WIN_X = 100;
constexpr int ENGINE_WIN_Y = 100;

// Window Size (With editor UI)
constexpr int ENGINE_WIN_H = TOP_PANEL_H + SCENE_WIN_H + OBJECTS_PANEL_H;
constexpr int ENGINE_WIN_W = HIERARCHY_PANEL_W + SCENE_WIN_W + INSPECTOR_PANEL_W;

#endif