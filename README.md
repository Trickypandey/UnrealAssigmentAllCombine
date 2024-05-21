# UnrealAssigment
README for Unreal Engine Assignment Week 4
Part 1: Define Data Structures and Data Assets
Create Data Structures:

Define C++ structs FMeshData, FMaterialData, and FTextureData to store references and other relevant properties of meshes, materials, and textures.
Implement Data Assets:

Develop a UDataAsset class named UMeshAssetManager, which will store arrays of FMeshData, FMaterialData, and FTextureData, organizing and providing easy access to these resources.
Part 2: Development of the Slate Widget and UserWidget Integration
Develop the Slate Widget:

Create a C++ class SMeshSelectionScrollBox derived from SCompoundWidget. This widget will feature a horizontal scroll box that dynamically displays options from UMeshAssetManager, including thumbnails and text for each asset.
Include an enumeration input to determine the asset type (mesh, material, or texture) being displayed.
Create and Configure MeshSelectionScrollBox UWidget:

Develop a UWidget called MeshSelectionScrollBox that utilizes the SMeshSelectionScrollBox.
Add two editable properties for passing the UMeshAssetManager data asset and the enumeration that specifies the asset type.
Integrate the Slate Widget into a UserWidget:

Construct a new C++ class USelectionWidget derived from UUserWidget.
Create a widget blueprint from this class and incorporate the MeshSelectionScrollBox into the blueprint.
Pass the data asset as its input parameter to populate the UI with relevant data based on the selected asset type.
Part 3: Custom Player Controller for Mesh Management
Develop the Player Controller:

Create a custom player controller named AInteractiveArchController. This controller will manage the logic for spawning and replacing meshes through the USelectionWidget.
Implement input bindings to enable floor selection via mouse left-click, where the USelectionWidget instance is displayed, and to hide the UI when the Tab key is pressed.
Implement Mesh Placement and Replacement Logic:

Enable functionality to spawn a selected mesh at the chosen location.
Develop logic to communicate selected asset data from USelectionWidget to the controller for spawning.
Create a custom actor AArchMeshActor derived from AStaticMeshActor for placement.
Implement logic to replace the previous mesh if another mesh is selected without changing the location.
Part 4: Material and Texture Customization
Extend UI for Additional Selections:

Modify USelectionWidget to display additional scrollable widgets for materials and textures when a spawned AArchMeshActor is selected.
Ensure the mesh selection box remains available for additional mesh placements.
Integrate Functionality for Customizing Mesh Actors:

Implement features within AInteractiveArchController and USelectionWidget to replace meshes or change materials and textures of the static mesh component inside AArchMeshActor based on the selected thumbnail from the UI.
Part 5: Integrate with Assignment 3
Integrate the Assignment 3:

Maintain a single project for consistency, integrating all assignments into one custom plugin.
Use the same player controller from Assignment 3 for this assignment.
Implement Multiple Camera Views:

Integrate three distinct camera views into the player controller:
Perspective View: The default camera view offering a 3D perspective.
Isometric View: Fixed at an angle that simulates a three-dimensional environment on a two-dimensional plane.
Orthographic View: A top-down view perfect for detailed adjustments and fine placements.
Implement camera control logic within AInteractiveArchController to allow dynamic switching between these views using key bindings:
Press P to switch between perspective, isometric, and orthographic views.
Press C to change the game mode.
Implement tailored control schemes for each perspective.
Setup Instructions
Clone the Repository:

sh
Copy code
git clone <repository-url>
Open the Project in Unreal Engine:

Open the Unreal Engine Editor.
Navigate to the project directory and open the .uproject file.
Compile the Project:

Use the Compile button in the Unreal Engine Editor to compile the project.
Setup Game Mode:

To switch between different game modes, press the C key during gameplay.
To change the camera perspective, press the P key to toggle between perspective, isometric, and orthographic views.
Project Structure
Source Folder:
Contains the C++ source files for the project.
Custom Plugin:
All assignments are maintained within a single custom plugin to ensure consistency and manageability.
UMeshAssetManager:
Stores arrays of mesh, material, and texture data.
SMeshSelectionScrollBox:
Custom Slate widget for displaying mesh, material, and texture options.
USelectionWidget:
User widget that incorporates the SMeshSelectionScrollBox for selection and customization.
Player Controls
Mouse Left-Click:
Selects the floor or spawns the selected mesh at the clicked location.
Tab:
Toggles the visibility of the USelectionWidget.
P:
Switches between perspective, isometric, and orthographic camera views.
C:
Changes the game mode.