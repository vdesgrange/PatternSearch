#include "../../include/CLI.hpp"

CLI::CLI() {
    mat = nullptr;
}

CLI::~CLI() {
}

/**
 * getMatrice
 * @brief Matrice getter.
 * @return {Matrice*} Pointer to a matrice.
 */
Matrice* CLI::getMatrice() {
    return this->mat;
}

/**
 * setMatrice
 * @brief Matrice setter.
 * @param {Matrice*} Pointer to a matrice.
 */
void CLI::setMatrice(Matrice *mat) {
    this->mat = mat;
}

/**
 * processUserEntry
 * @brief process the user entry
 * @param {string} user entry
 */
Action CLI::processUserEntry(string entry) {
    regex operationRe("searchSequence|searchClosestMatch|searchUnordered");
    regex itemRe("-?[0-9]+");
    smatch operationMatch, itemMatch;

    map<string, Operation> op;
    op["searchSequence"] = Operation::searchSequence;
    op["searchUnordered"] = Operation::searchUnordered;
    op["searchClosestMatch"] = Operation::searchClosestMatch;

    istringstream stream(entry);
    Action action;
    int item(0);
    vector<int> sequence;

    auto item_begin = sregex_iterator(entry.begin(), entry.end(), itemRe);
    auto item_end = sregex_iterator();

    if (entry == "exit")
        return {};

    if (regex_search(entry, operationMatch, operationRe)) {
        // Find one search operation
        if (operationMatch.size() == 1) {

            try {
                action.op = op[operationMatch[0]];
                // Iterate on all item (considered as single values).
                for (sregex_iterator it = item_begin; it != item_end; ++it) {
                    itemMatch = *it;
                    item = stoi(itemMatch.str());
                    sequence.push_back(item);
                }
                action.sequence = sequence;
            } catch (const out_of_range& err) {
                cout << "Unrecognised operation." << endl;
                return {};
            }

            // Return processed entry action.
            return action;
        } else {
            cout << "Unrecognised operation. \n"
                << "Please enter : \n"
                << "`searchSequence` or `searchUnordered` or `searchClosestMatch`." << endl;
        }
    }

    return {};
}

/**
 * actionController
 * @brief Handle user action
 * @param {Action} action - action of the user, contain operation type and pattern of research.
 * @return {string} action result
 */
string CLI::actionController(Action action) {
    return Processing::applySearch(action.op, this->mat, action.sequence);
}

/**
 * displayResult
 * @brief Display an action result.
 * @param {Action} action
 * @param {string} result
 * @return {void}
 */
void CLI::displayResult(Action action, string result) {
    if (!result.empty()) {
        cout << "Operation succeed. Operation results are the following : \n";
        cout << result << endl;
    } else {
        cout << "No matching." << endl;
    }
    return;
}

void CLI::workflow(Matrice* mat) {
    Action action;
    string userEntry;
    string result;

    if (mat == nullptr) {
        cout << "No valid matrice was found. \n"
           <<  "Please verify if program arguments are valid."
           << endl;
        return;
    }

    this->setMatrice(mat);

    cout << "Command Line Interface \n"
        << "###### HELP ###### \n"
        << "exit - Quit \n"
        << "Entry a command following above formats : \n"
        << "   searchSequence integer+\n"
        << "   searchClosestMatch integer+\n"
        << "   searchUnorderedMatch integer+\n"
        << "-----------------------------\n"
        << "Example : searchSequence 10 23 234"
        << endl;

    while (userEntry != "exit") {
        cout << ">> ";
        getline(cin, userEntry);
        action = processUserEntry(userEntry);
        result = actionController(action);
        displayResult(action, result);
    }

    cout << "###### EXIT ######" << endl;

    return;
}
