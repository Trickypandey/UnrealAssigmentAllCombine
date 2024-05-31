# Unreal Engine Assignment Week 


   ### Objective

Develop a procedural fence system in Unreal Engine using C++. The system should use splines to spread fences along a path, allowing for customizable parameters such as shape, length, height, and spacing. The vertical rail meshes for the fence need to be procedural mesh, with custom shape designs.

### Features

1. **Initial Classes**:
   - `FFenceProperties` for managing fence characteristics such as length, width, height, and spacing.
   - `AFenceMeshActor` for procedural fence generation along splines.
   - `AVerticalRailActor` for defining the shape and size of vertical rails.

2. **Procedural Mesh Component for Vertical Rails**:
   - Procedural generation of different types of vertical fence rail meshes.
   - Each vertical mesh consists of:
     - Bottom Part: A fixed part.
     - Top Part: A customizable part that can interpolate (lerp) between different designs.
   - Construction script integration.

3. **Fence Actor Class Modification**:
   - Construction script spawns vertical and horizontal meshes along the spline path.
   - Replaces static meshes with procedural mesh actors upon game start.

4. **Material Creation and Application**:
   - Custom wooden material with parameters for color and textures.
   - Dynamic material instances with UV tiling adjustments for stretched meshes.

5. **Customization**:
   - Adjustable fence height and horizontal fence width.

### Usage Instructions

1. **Change Game Mode**:
   - Switch to `BP_ProMeshGameMode`.
   - Add `BP_Fence` from the plugin content to the viewport.

2. **Customization Options**:
   - Change the length and spacing of the fence.
   - Adjust the width of the horizontal fence.


   ### Demo

[Watch the demo video](https://zuruinc-my.sharepoint.com/:v:/g/personal/sourabh_pandey_zuru_com/EUUjZCXRqGZPuyRDymsubEwBD2rJecxdua1AijQ2ueIqPQ?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=LNS3Q6)



## Objective

The goal of this project is to develop a system in Unreal Engine using C++ that allows players to interact with the user interface to spawn static meshes in the game environment. Players will be able to select different meshes and materials from a UI menu, place these objects within the game world, replace them with alternative selections, and customize their appearances by changing materials and textures.

## Task Breakdown

### Part 1: Define Data Structures and Data Assets

1. **Create Data Structures**:
    - Define C++ structs `FMeshData`, `FMaterialData`, and `FTextureData` to store references and other relevant properties of meshes, materials, and textures.

2. **Implement Data Assets**:
    - Develop a `UDataAsset` class named `UMeshAssetManager`, which will store arrays of `FMeshData`, `FMaterialData`, and `FTextureData`, organizing and providing easy access to these resources.

### Part 2: Development of the Slate Widget and UserWidget Integration

1. **Develop the Slate Widget**:
    - Create a C++ class `SMeshSelectionScrollBox` derived from `SCompoundWidget`. This widget will feature a horizontal scroll box that dynamically displays options from `UMeshAssetManager`, including thumbnails and text for each asset.
    - Include an enumeration input to determine the asset type (mesh, material, or texture) being displayed.

2. **Create and Configure `MeshSelectionScrollBox` UWidget**:
    - Develop a UWidget called `MeshSelectionScrollBox` that utilizes the `SMeshSelectionScrollBox`.
    - Add two editable properties for passing the `UMeshAssetManager` data asset and the enumeration that specifies the asset type.

3. **Integrate the Slate Widget into a UserWidget**:
    - Construct a new C++ class `USelectionWidget` derived from `UUserWidget`.
    - Create a widget blueprint from this class and incorporate the `MeshSelectionScrollBox` into the blueprint.
    - Pass the data asset as its input parameter to populate the UI with relevant data based on the selected asset type.

### Part 3: Custom Player Controller for Mesh Management

1. **Develop the Player Controller**:
    - Create a custom player controller named `AInteractiveArchController`. This controller will manage the logic for spawning and replacing meshes through the `USelectionWidget`.
    - Implement input bindings to enable floor selection via mouse left-click, where the `USelectionWidget` instance is displayed, and to hide the UI when the Tab key is pressed.

2. **Implement Mesh Placement and Replacement Logic**:
    - Enable functionality to spawn a selected mesh at the chosen location.
    - Develop logic to communicate selected asset data from `USelectionWidget` to the controller for spawning.
    - Create a custom actor `AArchMeshActor` derived from `AStaticMeshActor` for placement.
    - Implement logic to replace the previous mesh if another mesh is selected without changing the location.

### Part 4: Material and Texture Customization

1. **Extend UI for Additional Selections**:
    - Modify `USelectionWidget` to display additional scrollable widgets for materials and textures when a spawned `AArchMeshActor` is selected.
    - Ensure the mesh selection box remains available for additional mesh placements.

2. **Integrate Functionality for Customizing Mesh Actors**:
    - Implement features within `AInteractiveArchController` and `USelectionWidget` to replace meshes or change materials and textures of the static mesh component inside `AArchMeshActor` based on the selected thumbnail from the UI.

### Part 5: Integrate with Assignment 3

1. **Integrate Assignment 3**:
    - Maintain a single project for consistency, integrating all assignments into one custom plugin.
    - Use the same player controller from Assignment 3 for this assignment.

2. **Implement Multiple Camera Views**:
    - Integrate three distinct camera views into the player controller:
        - **Perspective View**: The default camera view offering a 3D perspective.
        - **Isometric View**: Fixed at an angle that simulates a three-dimensional environment on a two-dimensional plane.
        - **Orthographic View**: A top-down view perfect for detailed adjustments and fine placements.
    - Implement camera control logic within `AInteractiveArchController` to allow dynamic switching between these views using key bindings:
        - **Press P** to switch between perspective, isometric, and orthographic views.
        - **Press C** to change the game mode.
    - Implement tailored control schemes for each perspective.

## Setup Instructions

1. **Clone the Repository**:
    ```sh
    git clone <repository-url>
    ```

2. **Open the Project in Unreal Engine**:
    - Open the Unreal Engine Editor.
    - Navigate to the project directory and open the `.uproject` file.

3. **Compile the Project**:
    - Use the `Compile` button in the Unreal Engine Editor to compile the project.

4. **Setup Game Mode**:
    - To switch between different game modes, press the **C** key during gameplay.
    - To change the camera perspective, press the **P** key to toggle between perspective, isometric, and orthographic views.

## Project Structure

- **Source Folder**:
    - Contains the C++ source files for the project.
- **Custom Plugin**:
    - All assignments are maintained within a single custom plugin to ensure consistency and manageability.
- **UMeshAssetManager**:
    - Stores arrays of mesh, material, and texture data.
- **SMeshSelectionScrollBox**:
    - Custom Slate widget for displaying mesh, material, and texture options.
- **USelectionWidget**:
    - User widget that incorporates the `SMeshSelectionScrollBox` for selection and customization.

## Player Controls

- **Mouse Left-Click**:
    - Selects the floor or spawns the selected mesh at the clicked location.
- **Tab**:
    - Toggles the visibility of the `USelectionWidget`.
- **P**:
    - Switches between perspective, isometric, and orthographic camera views.
- **C**:
    - Changes the game mode.

## Integration with Assignment 3

This project is integrated with Assignment 3 and maintains consistency across assignments within a single custom plugin. The player controller used in Assignment 3 is also utilized here, with additional features for mesh spawning, customization, and camera control.

## Contribution

If you would like to contribute to this project, please fork the repository and submit a pull request. For major changes, please open an issue first to discuss what you would like to change.

