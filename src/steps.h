#ifndef STEPS_H
#define STEPS_H

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

enum class stepTypes {
    TitleStep,
    TextStep,
    TextInputStep,
    NumberInputStep,
    CalculusStep,
    DisplayStep,
    TextFileStep,
    CsvFileStep,
    OutputStep,
    EndStep

};

class Step {
  public:
    virtual void execute() = 0;
    virtual bool userInteraction() = 0;
    virtual string getInput() = 0;
    virtual float getNumberInput() = 0;
    virtual stepTypes getType() = 0;
    virtual ~Step() = default;
};

class TitleStep : public Step {
  private:
    string title;
    string subtitle;

  public:
    TitleStep(const string &title, const string &subtitle)
        : title(title), subtitle(subtitle) {}

    void execute() override {}
    string getInput() override {}
    float getNumberInput() override {}
    bool userInteraction() override {
        cout << "Please enter: 'retry', 'skip' or 'done'" << endl;
        string input;
        cin >> input;
        if (userInteraction()) {
            if (input == "retry") {
                execute();
                return true;
            } else if (input == "skip") {
                return false;
            } else if (input == "done") {
                return true;
            } else {
                cerr << "Invalid input! Please enter: 'retry', 'skip' or 'done'"
                     << endl;
                return userInteraction();
            }
        }
    }
    stepTypes getType() override { return stepTypes::TitleStep; }
};

class TextStep : public Step {
  private:
    string title;
    string copy;

  public:
    TextStep(const string &title, const string &copy)
        : title(title), copy(copy) {}

    void execute() override {
        cout << "Text Step " << endl
             << "Title: "
             << " " << title << " Copy: "
             << " " << copy << endl;
    }
    bool userInteraction() override {
        cout << "Please enter: 'retry', 'skip' or 'done'" << endl;
        string input;
        cin >> input;
        if (userInteraction()) {
            if (input == "retry") {
                execute();
                return true;
            } else if (input == "skip") {
                return false;
            } else if (input == "done") {
                return true;
            } else {
                cerr << "Invalid input! Please enter: 'retry', 'skip' or 'done'"
                     << endl;
                return userInteraction();
            }
        }
    }
    string getInput() override {}
    float getNumberInput() override {}
    stepTypes getType() override { return stepTypes::TextStep; }
};

class TextInputStep : public Step {
  private:
    string description;
    string textInput;

  public:
    TextInputStep(const string &description) : description(description) {}

    void execute() override {
        cout << "Text Input Step " << endl
             << "Description: "
             << " " << description << " "
             << "Input Text: ";
        getline(cin, textInput);
    }
    string getInput() override { return textInput; }
    float getNumberInput() override {}
    bool userInteraction() override {
        cout << "Please enter: 'retry', 'skip' or 'done'" << endl;
        string input;
        cin >> input;
        if (userInteraction()) {
            if (input == "retry") {
                execute();
                return true;
            } else if (input == "skip") {
                return false;
            } else if (input == "done") {
                return true;
            } else {
                cerr << "Invalid input! Please enter: 'retry', 'skip' or 'done'"
                     << endl;
                return userInteraction();
            }
        }
    }
    stepTypes getType() override { return stepTypes::TextInputStep; }
};

class NumberInputStep : public Step {
  private:
    string description;
    float numberInput;

  public:
    NumberInputStep(const string &description) : description(description) {}

    void execute() override {
        cout << "Number Input Step" << endl
             << "Description: "
             << " " << description << " "
             << "Input Number: ";
        cin >> numberInput;
    }
    string getInput() override {}
    float getNumberInput() override { return numberInput; }
    bool userInteraction() override {
        cout << "Please enter: 'retry', 'skip' or 'done'" << endl;
        string input;
        cin >> input;
        if (userInteraction()) {
            if (input == "retry") {
                execute();
                return true;
            } else if (input == "skip") {
                return false;
            } else if (input == "done") {
                return true;
            } else {
                cerr << "Invalid input! Please enter: 'retry', 'skip' or 'done'"
                     << endl;
                return userInteraction();
            }
        }
    }
    stepTypes getType() override { return stepTypes::NumberInputStep; }
};

enum class Operations {
    Add,
    Substract,
    Multiply,
    Divide,
    Min,
    Max

};

Operations getOperation(const string &operation) {
    if (operation == "+") {
        return Operations::Add;
    } else if (operation == "-") {
        return Operations::Substract;
    } else if (operation == "*") {
        return Operations::Multiply;
    } else if (operation == "/") {
        return Operations::Divide;
    } else if (operation == "Min") {
        return Operations::Min;
    } else if (operation == "Max") {
        return Operations::Max;
    } else {
        cerr << "Invalid operation" << endl;
        return Operations::Add;
    }
}

class CalculusStep : public Step {
  private:
    int steps;
    string operation;
    vector<Step *> stepsToCalculate;
    float result;

  public:
    CalculusStep(int steps, const string &operation)
        : steps(steps), operation(operation) {}

    void execute() override {
        cout << "Calculus Step: "
             << "step " << steps << " " << operation << " step " << steps
             << endl;
        this->result = doOperation(getOperation(operation));
        cout << "Result: " << result << endl;
    }

    void setInputSteps(const vector<Step *> &inputs) {
        stepsToCalculate = inputs;
    }

    bool userInteraction() override {
        for (int i = 1; i <= steps; i++) {
            Step *stepToCalculate = stepsToCalculate[i];
            if (stepToCalculate->userInteraction()) {
                stepToCalculate->execute();
            } else {
                return false;
            }
        }
        return true;
    }

    stepTypes getType() override { return stepTypes::CalculusStep; }

    float doOperation(Operations op) {
        vector<float> numbers;
        for (const auto &stepToCalculate : stepsToCalculate) {
            if (stepToCalculate->getType() == stepTypes::NumberInputStep) {
                NumberInputStep *numberInputStep =
                    dynamic_cast<NumberInputStep *>(stepToCalculate);
                numbers.push_back(numberInputStep->getNumberInput());
            } else {
                cerr << "Invalid step type! (calculs)" << endl;
            }
        }
        return doOperation(op, numbers);
    }
    float doOperation(Operations op, const vector<float> &numbers) {
        switch (op) {
        case Operations::Add:
            return accumulate(numbers.begin(), numbers.end(), 0, plus<float>());
        case Operations::Substract:
            return accumulate(numbers.begin(), numbers.end(), 0,
                              minus<float>());
        case Operations::Multiply:
            return accumulate(numbers.begin(), numbers.end(), 0,
                              multiplies<float>());
        case Operations::Divide:
            if (any_of(numbers.begin() + 1, numbers.end(),
                       [](float number) { return number == 0; })) {
                cerr << "Cannot divide by 0" << endl;
                return 0;
            }
            return accumulate(numbers.begin(), numbers.end(), numbers[0],
                              divides<float>());
        case Operations::Min:
            return *min_element(numbers.begin(), numbers.end());
        case Operations::Max:
            return *max_element(numbers.begin(), numbers.end());
        default:
            cerr << "Invalid operation" << endl;
            return 0;
        }
    }
    string getInput() override {}

    float getNumberInput() override { return result; }
};

class DisplayStep : public Step {
  private:
    int step;
    string fileName;

  public:
    DisplayStep(int step, const string fileName)
        : step(step), fileName(fileName) {}

    void execute() override {
        cout << "Text File Step " << endl;
        cout << "Showing content for step: " << step << endl;
        cout << "File Name: " << fileName << endl;

        string extension = fileName.substr(fileName.find_last_of(".") + 1);
        if (extension == "txt" || extension == "csv") {
            ifstream file(fileName);
            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    cout << line << endl;
                }
                file.close();
            } else {
                cerr << "Failed to open file: " << fileName << endl;
            }
        }
    }
    bool userInteraction() override {}
    string getInput() override {}
    float getNumberInput() override {}

    stepTypes getType() override { return stepTypes::DisplayStep; }
};

class TextFileStep : public Step {
  private:
    string description;
    string fileName;

  public:
    TextFileStep(const string &description, const string &fileName)
        : description(description), fileName(fileName) {}

    void execute() override {
        cout << "Text File Step " << endl;
        cout << "Description: " << description << endl;
        cout << "File Name: " << fileName << endl;
        cout << "Successfully added file to the flow." << endl;
    }
    string getInput() override {}
    float getNumberInput() override {}
    bool userInteraction() override {
        cout << "Please enter: 'retry', 'skip' or 'done'" << endl;
        string input;
        cin >> input;
        if (userInteraction()) {
            if (input == "retry") {
                execute();
                return true;
            } else if (input == "skip") {
                return false;
            } else if (input == "done") {
                return true;
            } else {
                cerr << "Invalid input! Please enter: 'retry', 'skip' or 'done'"
                     << endl;
                return userInteraction();
            }
        }
    }
    stepTypes getType() override { return stepTypes::TextFileStep; }
};

class CsvFileStep : public Step {
  private:
    string description;
    string fileName;

  public:
    CsvFileStep(const string &description, const string &fileName)
        : description(description), fileName(fileName) {}
    void execute() override {
        cout << "CSV File Step " << endl;
        cout << "Description: " << description << endl;
        cout << "File Name: " << fileName << endl;
        cout << "Successfully added file to the flow." << endl;
    }
    string getInput() override {}
    float getNumberInput() override {}
    bool userInteraction() override {
        cout << "Please enter: 'retry', 'skip' or 'done'" << endl;
        string input;
        cin >> input;
        if (userInteraction()) {
            if (input == "retry") {
                execute();
                return true;
            } else if (input == "skip") {
                return false;
            } else if (input == "done") {
                return true;
            } else {
                cerr << "Invalid input! Please enter: 'retry', 'skip' or 'done'"
                     << endl;
                return userInteraction();
            }
        }
    }
    stepTypes getType() override { return stepTypes::CsvFileStep; }
};

class OutputStep : public Step {
  private:
    int steptoOutput;
    string fileName;
    string title;
    string description;
    vector<string> text;

  public:
    OutputStep(const string &fileName, const string &title,
               const string &description, const vector<string> &text)
        : fileName(fileName), title(title), description(description),
          text(text) {}
    void execute() override {
        cout << "Output Step" << endl;
        cout << "Writing to file: " << fileName << endl;

        ofstream file(fileName);
        if (file.is_open()) {
            file << "Title: " << title << endl;
            file << "Description: " << description << endl;
            file << "Text: " << endl;
            for (const auto &line : text) {
                file << line << endl;
            }
            file.close();
            cout << "File written successfully" << endl;
        } else {
            cerr << "Error: Unable to open file " << fileName << endl;
        }
    }
    string getInput() override {}
    float getNumberInput() override {}
    bool userInteraction() override {
        cout << "Please enter: 'retry', 'skip' or 'done'" << endl;
        string input;
        cin >> input;
        if (userInteraction()) {
            if (input == "retry") {
                execute();
                return true;
            } else if (input == "skip") {
                return false;
            } else if (input == "done") {
                return true;
            } else {
                cerr << "Invalid input! Please enter: 'retry', 'skip' or 'done'"
                     << endl;
            }
        }
    }
    stepTypes getType() override { return stepTypes::OutputStep; }
};

#endif