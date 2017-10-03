#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "AssemblyLine.h"
#include "ItemManager.h"
#include "OrderManager.h"
#include "Item.h"
#include "Processor.h"
#include "Task.h"

void AssemblyLine::push_back(Processor&& p) {
	emplace_back(std::move(p));
}

void AssemblyLine::validate(std::ostream& cerr) {
	//Iterate through each Assembly (Derived from Processor, Processor derived from Task Base Class
	for (auto this_task = begin(); this_task != end(); this_task++) {
		bool validated = false;
		//For each Assembly Task, compare it with the rest of the tasks to match names.
		for (auto other_task = begin(); other_task != end() && !validated; other_task++) {
			if (this_task->getName() != other_task->getName()) {
				validated = this_task->validate(*other_task);
			}
		}
		if (!validated) {
			cerr << "The task " << this_task->getName() << " is not validated." << std::endl;
		}
	}
}

void AssemblyLine::display(std::ostream& os) const {
	for (auto p = begin(); p != end(); p++) {
		p->display(os);
	}
}

void AssemblyLine::validate(ItemManager& im, std::ostream& cerr){


    //OUTER LOOP, iterate each item in our inventory list.
	for (auto this_item = im.begin(); this_item != im.end(); this_item++) {
		//INNER LOOP, for every item, iterate through the task list, to check
		//if the item's installer task is in the task list.
		auto filler_found = std::find_if(begin(), end(), [&](Task t) {
			if (this_item->getFiller() == t.getName()) {
				return true;
			}
			return false;
		});
		if (filler_found == end()) {
			cerr << this_item->getFiller() << " is unavailable" << std::endl;
		}
		//AND THEN THE SAME LOOP TO FIND REMOVER...
		auto remover_found = std::find_if(begin(), end(), [&](Task t) {
			if (this_item->getRemover() == t.getName()) {
				return true;
			}
			return false;
		});
		if (remover_found == end()) {
			cerr << this_item->getRemover() << " is unavailable" << std::endl;
		}
	}

}


void AssemblyLine::loadItem(ItemManager& im){

    //Iterate through each task, and load each task
    //with the pointer to the item it processes
    for(auto processor = begin(); processor != end(); processor++){
        bool filled = false;

        for(auto item = im.begin(); item != im.end() && !filled ; item++){
            if(processor->getName() == item->getFiller()  ||
               processor->getName() == item->getRemover()){
                processor->load(*item);
                filled = true;
            }
        }

    }
}

void AssemblyLine::loadOrders(OrderManager& om, const std::string& starting_point, std::ostream& cerr){

    //Iterate through the Processors, to find the starting point.
    auto starting_point_found = std::find_if(begin(), end(), [&](Processor p){return p.getName() == starting_point;    });
    if(starting_point_found != end()){
       while(!om.empty()){
        std::unique_ptr<CustomerOrder> order(new CustomerOrder(std::move(om.extract())));
        starting_point_found->accept(std::move(*order));
        om.pop_back();
       }
    }
}




bool AssemblyLine::process(OrderManager& om, unsigned int pause){
    bool not_done = false;
    for( unsigned int step = 0; step < pause ; step++){
        //Advance each processor by one step
        for(auto& p: *this){
            p.advance();
        }
        //Check if each processor is ready to ship or ready to pass

        for(auto& p: *this){
            if (p.readyToShip()){
                p.ship(om);
            }else if(p.readyToPass()){
                srand(time(NULL));
                int inspection_score = rand() % 101;
                p.pass(inspection_score);
            }
        }
        size_t active_processors = size();
        //Check if all processors are empty, decreasing each active processor count by one if an empty processor is found
        //if there are 0 active processors left, then set done to true, and the simulation is done.

        for(auto& p: *this){
            if (p.empty()){ --active_processors; }
        }
        if(active_processors == 0){ return true; }
       // std::cout << std::setw(50) << std::setfill('=') << '=' << std::setfill('\0') << std::setw(0) << std::endl;
    }
    return not_done;
}
