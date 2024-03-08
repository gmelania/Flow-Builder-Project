#include "flows.h"
#include "steps.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {

    string ans;

    cout << "Welcome to our new Flow App!" << endl;
    cout << endl;
    cout << "Here is the description of the steps you can use in order to "
            "create your "
            "own customised flow:"
         << endl;
    cout << "1. TITLE step: title, subtitle" << endl;
    cout << "2. TEXT step: title, copy" << endl;
    cout << "3. TEXT INPUT step: description, text input" << endl;
    cout << "4. NUMBER INPUT step: description, number input" << endl;
    cout << "5. CALCULUS step: 2 steps, operation" << endl;
    cout << "6. DISPLAY steps: step" << endl;
    cout << "7. TEXT FILE input step: description, file_name" << endl;
    cout << "8. CSV FILE input step: description, file_name" << endl;
    cout << "9. OUTPUT step: step, name of file, title "
            ", description"
         << endl;
    cout << "10. END step" << endl;

    while (true) {
        cout << "If you want to create your own flow, type 'create': ";
        string ans;
        cin >> ans;

        if (ans != "create") {
            cout << "Invalid answer. Please type 'create': ";
            continue;
        }

        manageFlows flows;
        cout << "The name of your custom flow: ";
        string flowName;
        cin.ignore();
        getline(cin, flowName);
        flows.createFlow(flowName);
        Flows flow(flowName);
        flow.start();
        int stepNumber = 100;
        while (stepNumber != 0) {
            cout << endl;
            cout << "Please enter the number of the step you want to add to "
                    "your new flow. Back to menu, press 0: ";
            cin >> stepNumber;
            switch (stepNumber) {
            case 1: {
                cout << endl;
                cout << "Description: "
                     << "Add a title and a subtitle" << endl;
                cout << "Enter Title: ";
                cin.ignore();
                string title;
                getline(cin, title);
                if (title.empty()) {
                    cerr << "Title cannot be empty.";
                }
                cout << "Enter Subtitle: ";
                string subtitle;
                getline(cin, subtitle);
                if (subtitle.empty()) {
                    cerr << "Subtitle cannot be empty.";
                }
                Step *titleStep = flows.buildTitleStep(title, subtitle);
                flows.addStepToFlow(flowName, titleStep);
                flows.addStepData(flowName, stepNumber, {title, subtitle});
                break;
            }
            case 2: {
                cout << endl;
                cout << "Step type: TEXT " << endl;
                cout << "Description: "
                     << "Add a title and a text paragraph" << endl;
                cout << "Enter Title: ";
                cin.ignore();
                string title;
                getline(cin, title);
                cout << "Enter Copy: ";
                string copy;
                getline(cin, copy);
                Step *textStep = flows.buildTextStep(title, copy);
                textStep->execute();
                flows.addStepToFlow(flowName, textStep);
                flows.addStepData(flowName, stepNumber, {title, copy});
                break;
            }
            case 3: {
                cout << endl;
                cout << "Step type: TEXT INPUT" << endl;
                cout << "Description: "
                     << "Add a description and a text paragraph" << endl;
                cout << "Enter Description: ";
                cin.ignore();
                string description;
                getline(cin, description);
                Step *textInputStep = flows.buildTextInputStep(description);
                textInputStep->execute();
                flows.addStepToFlow(flowName, textInputStep);
                flows.addStepData(flowName, stepNumber,
                                  {description, textInputStep->getInput()});
                break;
            }
            case 4: {
                cout << endl;
                cout << "Step type: NUMBER INPUT" << endl;
                cout << "Description: "
                     << "Add a description and a number" << endl;
                cout << "Enter Description: ";
                cin.ignore();
                string description;
                getline(cin, description);
                cin.clear();
                Step *numberInputStep = flows.buildNumberInputStep(description);
                numberInputStep->execute();
                flows.addStepToFlow(flowName, numberInputStep);
                flows.addStepData(
                    flowName, stepNumber,
                    {description,
                     to_string(numberInputStep->getNumberInput())});
                break;
            }
            case 5: {
                cout << endl;
                cout << "Step type: CALCULUS" << endl;
                cout << "Description: "
                     << "Add previous NUMBER steps, and an "
                        "operation for calculating with them"
                     << endl;
                cout << "Enter Steps: ";
                cin.ignore();
                int steps;
                cin >> steps;
                cout << "Enter Operation: ";
                string operation;
                cin.ignore();
                getline(cin, operation);
                // Create a CalculusStep
                Step *calculusStep = flows.buildCalculusStep(steps, operation);

                // Get the previously added NumberInputSteps
                vector<Step *> inputSteps =
                    flows.getFlow(flowName)->getStepsOfType(
                        stepTypes::NumberInputStep);

                // Set the input steps for the CalculusStep
                dynamic_cast<CalculusStep *>(calculusStep)
                    ->setInputSteps(inputSteps);

                // Execute the CalculusStep
                calculusStep->execute();

                // Add the CalculusStep to the flow
                flows.addStepToFlow(flowName, calculusStep);
                flows.addStepData(
                    flowName, stepNumber,
                    {operation, to_string(calculusStep->getNumberInput())});
                break;
            }
            case 6: {
                cout << endl;
                cout << "Step type: DISPLAY" << endl;
                cout << "Description: Add a previously introduced "
                        "filename (.txt or .csv) to be diplayed, and the "
                        "locating step of that file "
                     << endl;
                cout << "Enter Step to display: ";
                cin.ignore();
                int step;
                cin >> step;
                cout << "Enter File Name: ";
                string File;
                cin.ignore();
                getline(cin, File);
                Step *displayStep = flows.buildDisplayStep(step, File);
                displayStep->execute();
                flows.addStepToFlow(flowName, displayStep);
                flows.addStepData(flowName, stepNumber,
                                  {to_string(step), File});
                break;
            }
            case 7: {
                cout << endl;
                cout << "Step: TEXT FILE INPUT" << endl;
                cout << "Description: Add a .txt file" << endl;
                cout << "Enter Description: ";
                cin.ignore();
                string description;
                getline(cin, description);
                cout << "Enter filename: ";
                string File;
                getline(cin, File);
                Step *textFileStep = flows.buildTextFileStep(description, File);
                textFileStep->execute();
                flows.addStepToFlow(flowName, textFileStep);
                flows.addStepData(flowName, stepNumber, {description, File});
                break;
            }
            case 8: {
                cout << endl;
                cout << "Step type: CSV FILE INPUT" << endl;
                cout << "Description: Add a .csv file" << endl;
                cout << "Enter Description: ";
                cin.ignore();
                string description;
                getline(cin, description);
                cout << "Enter filename: ";
                string File;
                getline(cin, File);
                Step *csvFileStep = flows.buildCsvFileStep(description, File);
                csvFileStep->execute();
                flows.addStepToFlow(flowName, csvFileStep);
                flows.addStepData(flowName, stepNumber, {description, File});
                break;
            }
            case 9: {
                cout << endl;
                cout << "Step type: OUTPUT" << endl;
                cout << "Description: Add previous steps, a filename, a title, "
                        "and "
                        "the description of "
                        "the file being generated"
                     << endl;
                cout << "Enter the step number for the output: ";
                cin.ignore();
                int step;
                cin >> step;
                cout << "Enter File Name: ";
                string File;
                cin.ignore();
                getline(cin, File);
                cout << "Enter Title: ";
                string title;
                getline(cin, title);
                cout << "Enter Description: ";
                string description;
                cin >> description;
                Step *outputStep =
                    flows.buildOutputStep(File, title, description,
                                          flows.getStepData(flowName, step));
                outputStep->execute();
                flows.addStepToFlow(flowName, outputStep);
                break;
            }
            case 10: {
                cout << endl;
                cout << "Ending flow..." << endl;
                stepNumber = 0;
                flow.end();
                break;
            }
            default: {
                cout << "Invalid step number." << endl;
                break;
            }
            }
        }
        cout << endl;
        cout << "If you want to create another flow please type 'create' "
             << endl;
        cout << "If you want to use an existing flow please type 'use' "
             << endl;
        cout << "If you want to delete an existing flow please type "
                "'delete'"
             << endl;
        cout << "If you want to quit please type 'quit'" << endl;
        cin >> ans;
        if (ans == "use") {
            cout << "The existing flows are: " << endl;
            for (const auto &entry : flows.getFlows()) {
                cout << entry.first << endl;
            }
            cout << "Please enter the name of the flow you want to use: ";
            string flowName;
            cin.ignore();
            getline(cin, flowName);

            Flows *flow = flows.getFlow(flowName);
            if (flow) {

                cout << "Do you want to see analytics for this flow? "
                        "(yes/no): ";
                string showAnalyticsans;
                cin >> showAnalyticsans;

                if (showAnalyticsans == "yes") {
                    flow->Analystics();
                } else {
                    cout << "No analytics shown." << endl;
                }
            }
        } else if (ans == "delete") {
            cout << "The existing flows are: " << endl;
            for (const auto &entry : flows.getFlows()) {
                cout << entry.first << endl;
            }
            cout << "Please enter the name of the flow you want to delete: ";
            string flowName;
            cin.ignore();
            getline(cin, flowName);
            flows.deleteFlow(flowName); // deleting flow...

        } else if (ans == "quit") {
            break; // quitting application...
        } else {
            cout << "Invalid answer." << endl;
        }
    }
    return 0;
}
