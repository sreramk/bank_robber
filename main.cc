/*
 * main.cc
 *
 *  Created on: 27-Jun-2018
 *      Author: sreramk
 */

#include <iostream>
#include <vector>
#include <memory>
#include <stdint.h>

/*struct Region {
	int first;
	int last;
};*/

class CombinationState {
	std::vector <uint32_t> stateID;

	std::vector<bool> combination;

	//int totalCombinations;

	/// comb: true => set. False => gap
	bool next_combination (uint8_t level);

	void cur_combination( uint8_t level);

	int compute_total_combinations ();

	//static int fact (int val);

public:


	CombinationState(int pIDSize, int pCombinationSize);

	void reset();

	bool next_combination ();

	const std::vector<bool>& get_combination() {
		return combination;
	}

	int total_combinations();

	void debug_display ();

	int combination_length() {
		return combination.size();
	}

	int get_state_size() {
		return stateID.size();
	}

};

CombinationState::CombinationState(int pIDSize, int pCombinationSize) {

	for (int i = 0; i < pIDSize; i++) {
		stateID.push_back(i);
	}
	combination.resize(pCombinationSize);

	reset ();

	//totalCombinations = compute_total_combinations ();


}

/*int CombinationState::fact (int val) {

	int res = 1;

	while (val) {
		res = res * val;
		val--;
	}
	return res;
}

int CombinationState::compute_total_combinations () {
	int n = combination.size();
	int r = stateID.size();
	return ( fact(n)/ (fact(n-r) * fact(r) )) - 1;
}

int CombinationState::total_combinations() {
	return totalCombinations;
}*/


void CombinationState::debug_display () {
	for (auto iter : combination) {
		std::cout << iter << " ";
	}
	std::cout << "\n";
}

void CombinationState::reset() {
	std::fill (combination.begin(), combination.begin() + stateID.size(), false );
	std::fill (combination.begin() + stateID.size(), combination.end(), true );
}


bool CombinationState::next_combination() {
	return next_combination(stateID.size() - 1);
}


bool CombinationState::next_combination ( uint8_t level) {


	int curPos = stateID[level];
	curPos++;
	if (curPos < (combination.size() - stateID.size() + level + 1) ) {
		combination[curPos - 1] = true;
		combination[curPos] = false;
		stateID[level]++;

	} else {

		if (level == 0) {
			/// signifies final combination.
			return false;
		}

		bool res = next_combination (level - 1);
		if (!res) {
			// signifies final combination
			return false;
		}
		stateID[level] = stateID[level - 1] +1;
		combination[curPos - 1] = true;
		combination[stateID[level]] = false;
	}

	// signifies that the current combination is not the final one.
	return true;
}

/*
int sum_region_max_pair (int* array, int size, struct Region reg) {
	int i, temp1, temp2;
	temp1 = array[0];
	if (reg.first < reg.last) {
		for (i = reg.first; i <= reg.last; i++) {
			if (temp1 < array[i]) {
				temp1 = array[i];
				temp2 = temp1;
			}
		}
	} else {
		for (i = reg.first; i < size; i++) {
			if (temp1 < array[i]) {
				temp1 = array[i];
				temp2 = temp1;
			}
		}
		for (i = 0; i < reg.last; i++) {
			if (temp1 < array[i]) {
				temp1 = array[i];
				temp2 = temp1;
			}
		}
	}
	return temp1 + temp2;
}*/


class BankRobber {
	std::vector<int> vaults;
	std::vector<bool> chosenVaults;

	bool chosenVaultsChanged;

	std::unique_ptr<CombinationState> combinations;

	/// 0->chosen, 1-> not chosen

	int moneyStolen;

	int rsolve_pos(int pos) {
		return pos %  vaults.size() ;
	}

	void set_open_vaults (const std::vector<bool>& pChosenVaults) {
		chosenVaults = pChosenVaults;
		chosenVaultsChanged = true;
	}

	int steal_money (const std::vector<bool>& pChosenVaults);


	bool check_validity_of_chosen_vaults(const std::vector<bool>& pChosenVaults);

	bool chosen_vaults_changed() {
		return chosenVaultsChanged;
	}

	void reset_chosen_vaults_changed() {
		chosenVaultsChanged = false;
	}

public:

	BankRobber (const std::vector<int>& pVaults);

	int maximize_stolen_money ();

	int get_stolen_value() {
		return moneyStolen;
	}

	const std::vector<bool>& get_chosen_vaults() {
		return chosenVaults;
	}

	void debug_display ();


};



BankRobber::BankRobber (const std::vector<int>& pVaults) :
		vaults(pVaults), chosenVaultsChanged(false),moneyStolen(0) {

	if (pVaults.size() < 5) {
		throw std::string ("Error, the bank cannot have less than 5 vaults");
	}

}

void BankRobber::debug_display () {

	std::cout << "\n Chosen Vaults: \n";

	for (uint64_t i = 0 ; i < vaults.size(); i++) {
		std::cout << vaults[i] << " : " << ((chosenVaults[i])? std::string("Not chosen") :
				std::string("chosen")) << "\n";
	}

	std::cout << "\n Total money stolen = " << moneyStolen;

}

int BankRobber::maximize_stolen_money () {

	for (int i = 1; i < vaults.size(); i++) {

		reset_chosen_vaults_changed ();

		combinations = std::make_unique<CombinationState>(i, vaults.size());
		do {
			const std::vector<bool>& tempChosenVaults = combinations->get_combination();
			if (check_validity_of_chosen_vaults(tempChosenVaults)) {
				steal_money(tempChosenVaults);
			}
		}while (combinations->next_combination());

		if (!chosen_vaults_changed()) {
			/// the iteration process aborts here, as even if you increase the
			/// number of vaults to be stolen, you won't be getting anywhere.
			return moneyStolen;
		}

	}
	return moneyStolen;
}

bool BankRobber::check_validity_of_chosen_vaults
(const std::vector<bool>& pChosenVaults) {
	for (int i = 0; i < pChosenVaults.size(); i++) {

		int temp = 0;
		for (int j = i; j < i + 5; j++) {
			if (pChosenVaults[rsolve_pos(j)] == false) {
				temp++;
			}
			if (temp > 2) {
				return false; // invalid
			}
		}

	}
	return true; // valid
}


int BankRobber::steal_money (const std::vector<bool>& pChosenVaults) {

	int sum = 0;

	for (int i = 0; i < pChosenVaults.size(); i++) {
		sum += (pChosenVaults[i])? 0: vaults[i];
	}

	if (moneyStolen < sum) {
		moneyStolen = sum;
		set_open_vaults(pChosenVaults);
	}
	return sum;
}



int main () {
	/*CombinationState state(4, 14);

	state.debug_display();

	for (int i = 0; i < state.total_combinations(); i++) {
		state.next_combination();
		state.debug_display();
	}

	std::cout << "\n" << state.total_combinations();*/

	std::vector <int> vaults;
	int n;
	std::cout << "\n Enter the number of vaults :";
	std::cin  >> n;
	vaults.resize(n);

	for (uint64_t i = 0; i < n; i++) {
		std::cin >> vaults [i];
	}
	BankRobber robber (vaults);

	robber.maximize_stolen_money();

	robber.debug_display();

	return 0;
}
