#ifndef FLOWS_H
#define FLOWS_H
#include "steps.h"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
enum class FlowStatus { Completed, InProgress, NotStarted };

class Flows {
  private:
    vector<Step *> steps;
    string flowName;
    FlowStatus status;
    map<Step *, int> ErrorCount;
    chrono::system_clock::time_point creationTime;
    int startCount;
    int totalErrors;
    int skipedSteps;
    int errorScreen;
    int completedFlows;

  public:
    Flows(const string &flowName)
        : flowName(flowName), status(FlowStatus::NotStarted), startCount(0),
          totalErrors(0), skipedSteps(0), errorScreen(0), completedFlows(0) {
        creationTime = chrono::system_clock::now();
    }
    string getFlowName() { return flowName; }

    void addStep(Step *step) { steps.push_back(step); }

    void start() {
        status = FlowStatus::InProgress;
        startCount++;
        completedFlows = 0;
        skipedSteps = 0;
        errorScreen = 0;
        totalErrors = 0;
    }
    void end() {
        status = FlowStatus::Completed;
        completedFlows++;
    }

    void execute() {
        if (status != FlowStatus::InProgress) {
            cerr << "Flow is not started" << endl;
            return;
        }

        for (Step *step : steps) {
            try {
                step->execute();
            } catch (const exception &e) {
                cout << "Error: " << e.what() << endl;
                totalErrors++;
                ErrorCount[step]++;
            }
        }

        status = FlowStatus::Completed;
        completedFlows++;

        Analystics();
    }

    vector<Step *> getStepsOfType(stepTypes type) {
        vector<Step *> result;
        for (auto step : steps) {
            if (step->getType() == type) {
                result.push_back(step);
            }
        }
        return result;
    }

    void skip() {
        if (status == FlowStatus::InProgress) {
            skipedSteps++;
        } else {
            cerr << "Flow is not running!" << endl;
        }
    }

    void displayErrorScreen() {
        if (status == FlowStatus::InProgress) {
            errorScreen++;
        } else {
            cerr << "Flow is not running!" << endl;
        }
    }

    void Analystics() {
        auto now = chrono::system_clock::now();
        time_t creationTimeT = chrono::system_clock::to_time_t(creationTime);
        cout << "Analystics for flow " << flowName << ": " << endl;
        cout << "The flow was created at: " << ctime(&creationTimeT) << endl;
        cout << "Duration of the flow: "
             << chrono::duration_cast<chrono::seconds>(now - creationTime)
                    .count()
             << " seconds" << endl;
        cout << "The flow was started " << startCount << " times" << endl;
        cout << "The flow was completed " << completedFlows << " times" << endl;
        cout << "Steps skipped: " << skipedSteps << "times" << endl;
        cout << "Error screen was displayed: " << errorScreen << " times"
             << endl;
        cout << "Average number of errors: "
             << (completedFlows > 0 ? totalErrors / completedFlows : 0) << endl;
    }
};

class manageFlows {
  private:
    map<string, Flows *> flows;
    map<string, map<int, vector<string>>> stepData;

  public:
    void createFlow(const string &name) { flows[name] = new Flows(name); }
    void addStepToFlow(const string &flowName, Step *step) {
        if (flows.find(flowName) != flows.end()) {
            flows[flowName]->addStep(step);
        } else {
            cout << "Flow was not found." << endl;
        }
    }

    map<string, Flows *> &getFlows() { return flows; }

    Flows *getFlow(const string &flowName) {
        auto it = flows.find(flowName);
        if (it != flows.end()) {
            return it->second;
        } else {
            cout << "Flow was not found." << endl;
            return nullptr;
        }
    }
    void addStepData(const string &flowName, int stepNumber,
                     const vector<string> &data) {
        stepData[flowName][stepNumber] = data;
    }

    vector<string> getStepData(const string &flowName, int stepNumber) {
        if (flows.find(flowName) != flows.end()) {
            return stepData[flowName][stepNumber];
        } else {
            cout << "Flow was not found." << endl;
            return {};
        }
    }

    Step *buildTitleStep(const string &title, const string &subtitle) {
        return new TitleStep(title, subtitle);
    }
    Step *buildTextStep(const string &text, const string &copy) {
        return new TextStep(text, copy);
    }
    Step *buildTextInputStep(const string &description) {
        return new TextInputStep(description);
    }
    Step *buildNumberInputStep(const string &description) {
        return new NumberInputStep(description);
    }
    Step *buildCalculusStep(int steps, const string &operation) {
        return new CalculusStep(steps, operation);
    }
    Step *buildDisplayStep(int step, const string fileName) {
        return new DisplayStep(step, fileName);
    }
    Step *buildTextFileStep(const string &description, const string &file) {
        return new TextFileStep(description, file);
    }
    Step *buildCsvFileStep(const string &description, const string &file) {
        return new CsvFileStep(description, file);
    }
    Step *buildOutputStep(const string &fileName, const string &title,
                          const string &description,
                          const vector<string> &inputs) {
        return new OutputStep(fileName, title, description, inputs);
    }

    void startFlow(const string &flowName) {
        if (flows.find(flowName) != flows.end()) {
            flows[flowName]->start();
            flows[flowName]->execute();
        } else {
            cout << "Flow was not found." << endl;
        }
    }

    void deleteFlow(const string &flowName) {
        if (flows.find(flowName) != flows.end()) {
            delete flows[flowName];
            flows.erase(flowName);
            cout << "Flow was deleted." << endl;
        } else {
            cout << "Flow was not found." << endl;
        }
    }
};

#endif