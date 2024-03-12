# Flow Builder Project

### Description

The Flow Builder is a tool designed to help users create linear flows comprising various predefined steps. These steps offer to different types of interactions and operations, allowing users to create dynamic sequences of actions and decisions.

## Available Steps

* Title Step: Add a title and subtitle to introduce sections.
* Text Step: Add a title and copy for displaying text.
* Text Input Step: Add a description for expected text input.
* Number Input Step: Add a description of the expected numerical input.
* Calculus Step: Add two previous numerical inputs (steps) to combine them using mathematical operations.
  > Supported operations:  Addition (+), Subtraction (-), Multiplication (*), Division (/), Minimum (min), Maximum (max).

* Display Step: Add a file name to show content from previous steps.
  > Supported files: Text Input, CSV Input.
  
* Text File Input Step: Import a ".txt" file for processing.
* CSV File Input Step: Import a ".csv" file for processing.
* Output Step: Generate a text file with the provided information.
* End Step: Marks the end of the flow.

## User Stories

### Flow Building and Management
- Users:
  *  can build new linear flows using the predefined steps, viewing their descriptions.
  *  can run already created flows, progressing through all added steps.
  *  can skip and unlimitedly add any steps to a flow.
  *  can see analytics (`timestamp`), displayed for each flow.
  *  can delete flows from the system.

- Step Types and Requirements

Display step shows content from previous steps.
Display step shows content of supported file types.
Users can add TEXT FILE input steps for .txt files.
Users can add CSV FILE input steps for .csv files.
Output step generates text files as output.
Output step requires a name, title, and description for the generated file.
Output step can include information from previous steps.
End step signifies the end of a flow.
Users see error screen with message for incorrect inputs.
Error screen allows users to retry or skip steps.
Flow Navigation and Analytics
Users can navigate steps by completing actions or skipping.
Analytics include flow start/completion count, screen skip count, and error count.

Classes and objects represent the steps, flows, and analytics. Encapsulation limits access to implementation details, and inheritance helps with code reuse, enabling the extension of base step classes to create specialized types. Polymorphism promotes flexibility, treating diverse step types within flows, and abstractization provides templates for implementations to facilitate the creation of generic structures. Exception handling ensures system stability by managing runtime errors during a flow execution. 

### Getting Started
To start using the Flow Builder project, follow these steps:

1. Download the "src" directory and unzip it.
2. Open the "main.cpp" file and run the application.
3. Create a new flow and add steps according to your requirements.
4. Configure each step with the necessary inputs and settings.
5. Analyze flow performance using the provided analytics tools.
6. Delete flows that are no longer needed to maintain a clean workspace.

### Contributors
Ghirda Melania - Project Developer

Chis Daniel/POLITEHNICA Bucuresti National University for Science and Technology - Coordonator
