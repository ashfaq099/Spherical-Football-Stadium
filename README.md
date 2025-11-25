
# 🏟️ 3D Football Stadium Simulation — OpenGL 3.3

An interactive 3D football stadium built using **Modern OpenGL (3.3)** featuring realistic lighting, shading, textures, camera navigation, and game mechanics such as shooting a football at a moving target with dynamic scoring.

This project showcases a full real-time graphics pipeline implemented from scratch using shaders, custom meshes, lighting models, and a lightweight physics/logic system.

---

<p align="center">
  <img src="https://github.com/ashfaq099/Spherical-Football-Stadium/blob/main/Assets/Stadium.jpg" width="80%">
  <br><b>Stadium – Full External View</b>
</p>

<p align="center">
  <img src="https://github.com/ashfaq099/Spherical-Football-Stadium/blob/main/Assets/Inside%20stadium.jpg" width="80%">
  <br><b>Inside the Stadium – Field & Seating Area</b>
</p>

<p align="center">
  <img src="https://github.com/ashfaq099/Spherical-Football-Stadium/blob/main/Assets/Foootball%2CGoalbar%2CScoreboard.jpg" width="80%">
  <br><b>Football, Goal Bar & Dynamic Scoreboard</b>
</p>

## 🎬 Simulation

Experience the full interactive 3D stadium in action — including lighting effects, camera navigation, football shooting mechanics, and dynamic scoring.

<p align="center">
  <a href="https://youtu.be/JknAf630tek">
    <img src="https://github.com/ashfaq099/Spherical-Football-Stadium/blob/main/Assets/Stadium.jpg" width="70%" >
  </a>
  <br>
  <b>Click the image to watch the simulation on YouTube</b>
</p>

---

## 🚀 **Key Features**

### ✅ **Real-time 3D Stadium Environment**

* Complete stadium architecture: field, gallery seats, goalpost, floodlights
* Fully textured models (grass, ball, seats, scoreboard, game-over screen)
* Smooth camera navigation across the scene

### 🎮 **Interactive Game Mechanics**

* Shoot a football toward a target with angle control
* Moving target with difficulty levels
* Dynamic scoring & game-over state
* Restartable gameplay

### 💡 **Modern Lighting System**

Implemented entirely using OpenGL 3.3 shaders:

* Directional Light
* Point Lights (Floodlights)
* Spotlight
* Toggle individual lighting components
* Adjustable ambient/diffuse/specular properties

### 🎨 **Texture Mapping**

* High-quality textures loaded using **stb_image**
* Proper UV mapping on the football (sphere)
* Textured field, seats, scoreboard, and UI elements

### 🔧 **OpenGL 3.3 Programmable Pipeline**

* Custom **Vertex & Fragment Shaders**
* Phong Lighting Model
* VAO/VBO/EBO based rendering pipeline
* Manual sphere generation (latitude/longitude mesh)

---

## 🛠️ **Tech Stack**

| Category            | Tools         |
| ------------------- | ------------- |
| **Graphics API**    | OpenGL 3.3    |
| **Language**        | C/C++         |
| **Window & Input**  | GLFW          |
| **OpenGL Loader**   | GLAD          |
| **Extensions**      | GLEW          |
| **Math**            | GLM           |
| **Texture Loading** | stb_image     |
| **IDE**             | Visual Studio |
| **Shaders**         | GLSL          |



---

## 🏗️ **Project Architecture**

```
/src
 ├── main.cpp               # Core rendering loop + game logic
 ├── shader.h               # Shader compilation/management
 ├── camera.h / basic_camera.h
 ├── sphere.h               # Sphere mesh generation for football
 ├── pointLight.h
 ├── directionLight.h
 ├── spotLight.h
 ├── stb_image.cpp/h        # Texture loader
/shaders
 ├── vertexShaderPhong.vs
 ├── fragmentShaderPhong.fs
 ├── vertexShaderGouraud.vs
 ├── fragmentShaderGouraud.fs
 ├── *textured versions*
/textures
 ├── field.jpg
 ├── grass.jpg
 ├── scoreboard.jpg
 ├── gameover.jpg
 ├── football.png
```

---

## 🎮 **Controls**



### **Camera Movement**

| Key       | Action        |
| --------- | ------------- |
| W         | Move backward |
| S         | Move forward  |
| A         | Move right    |
| D         | Move left     |
| SPACE     | Move up       |
| LEFT CTRL | Move down     |
| ↑         | Pitch up      |
| ↓         | Pitch down    |
| ←         | Yaw left      |
| →         | Yaw right     |
| Q         | Roll left     |
| E         | Roll right    |

### **Football Shooting & Gameplay**

| Key | Action                  |
| --- | ----------------------- |
| J   | Increase shooting angle |
| L   | Decrease shooting angle |
| G   | Shoot the ball          |
| B   | Restart game            |
| I   | Difficulty level 1      |
| O   | Difficulty level 2      |
| P   | Difficulty level 3      |

### **Lighting Toggles**

| Key | Action                   |
| --- | ------------------------ |
| 1   | Toggle directional light |
| 2   | Toggle point light       |
| 3   | Toggle spotlight         |
| 4   | Toggle ambient           |
| 5   | Toggle diffuse           |
| 6   | Toggle specular          |
| ESC | Exit program             |

---

## 🧠 **Core Technical Concepts**

### 🔷 **Transformations**

Implemented using GLM

* Model Matrix
* View Matrix (camera)
* Projection Matrix (perspective)

### 🔷 **Phong Lighting Model**

* Ambient
* Diffuse
* Specular
  (All computed in fragment shader)

### 🔷 **Stadium & Football Modeling**

Your football uses:

* Latitude/longitude subdivision
* Per-vertex normals
* Spherical UV mapping


### 🔷 **Game Logic**

Includes:

* Linear trajectory equation
* Collision detection with goal bar
* Score increment/decrement rules
* Difficulty-based target movement


---

## 🏁 **How to Build & Run**

### **Prerequisites**

* Visual Studio (2019/2022 recommended)
* Install:

  * GLFW
  * GLAD
  * GLEW
  * GLM

### **Steps**

1. Clone the repository
2. Open the `.sln` file in Visual Studio
3. Configure include & lib directories for:

   * GLFW
   * GLEW
   * GLAD
   * GLM
4. Build & Run 

---
