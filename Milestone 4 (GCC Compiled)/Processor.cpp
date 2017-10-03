#include <iostream>
#include <iomanip>
#include <string>
#include <functional>

#include "Processor.h"
#include "CustomerItem.h"
#include "CustomerOrder.h"
#include "OrderManager.h"
#include "Task.h"
#include "Item.h"

Processor::Processor(const std::string& record, std::function<Task::Quality(int)> lambda) :Task(record) {

	item_ = nullptr; //the item_ pointer to nullptr
	inspector = lambda; //the inspector pointer to the function received
	num_end_slots = getSlots(); //the num_end_slots to the number of slots in the processor
	is_a_filler = true; //the is_a_filler flag to true
}

void Processor::display(std::ostream& os) const {
	Task::display(os);
	os << std::setw(field_width) << std::right << "Item to add" << " : " ;
	if(item_ && is_a_filler){
            item_->display(os, false);
	}else{
	    os << "---" << std::endl;
	}
}

void Processor::load(Item& i){
    item_ = &i;
    is_a_filler = (getName() == i.getRemover()) ? false : true;
}

void Processor::pass(int score){
    Task *t = nullptr;
    if(is_a_filler){
            if(!getNextTask(Quality::redirect)){
                    t = const_cast<Task*>(getNextTask(Quality::passed));
            }
            else{
                Quality inspection_score = inspector(score);
                t = const_cast<Task*>(getNextTask(inspection_score));
            }
    }else{
            t = const_cast<Task*>(getNextTask(Quality::passed));
    }
    Processor *p = static_cast<Processor*>(t);
    std::unique_ptr<CustomerOrder> completed_order(new CustomerOrder(std::move(complete.front())));
    complete.pop_front();
    p->accept(std::move(*completed_order));
}

void Processor::accept(CustomerOrder&& order){
    waiting.emplace_back(std::move(order));
}


void Processor::advance(){
    //Starting point... if there are no orders in the process queue, and there are awaiting orders to be processed.

//    if(process.empty() && !waiting.empty()){
//        unsigned int counter = (num_end_slots < waiting.size()) ? num_end_slots : waiting.size();
//        for(unsigned int waiting_order = 0; waiting_order < counter; waiting_order++){
//            std::unique_ptr<CustomerOrder> awaiting_order(new CustomerOrder(std::move(waiting.front())));
//            waiting.pop_front();
//            process.emplace_back(std::move(*awaiting_order));
//        }
//        num_end_slots = getSlots() - process.size();
//    }



//    If there is a task(s) on the process queue, process them accordingly,
//    if(!process.empty() && num_end_slots != 0){
//            num_end_slots = getSlots() - process.size();
//        for(auto order = process.begin(); order != process.end(); order++){
//            if(is_a_filler){
//                order->fill(*item_);
//            }else{
//                order->remove(*item_);
//            }
//        }
//    }
//    if(num_end_slots == 0){
//        std::unique_ptr<CustomerOrder> completed_order(new CustomerOrder(std::move(process.front())));
//        process.pop_front();
//        complete.emplace_back(std::move(*completed_order));
//        num_end_slots++;
//    }
//    Check to see if there are any awaiting orders to be processed.
//    But ONLY move them to the process queue if there are enough slots left.
//    if(!waiting.empty() && num_end_slots > 0){
//        std::unique_ptr<CustomerOrder> awaiting_order(new CustomerOrder(std::move(waiting.front())));
//        waiting.pop_front();
//        process.emplace_back(std::move(*awaiting_order));
//        num_end_slots--;
//    }
//    std::cout << "After => Processor: " << getName() << ": Has " << num_end_slots << "/" << getSlots() << " Left." << std::endl;
//}

}

bool Processor::empty()const{
    return (waiting.empty() && process.empty() && complete.empty());
}

bool Processor::readyToShip() const{
    return (!complete.empty() && (!getNextTask(Quality::passed) && !getNextTask(Quality::redirect)));
}

bool Processor::readyToPass() const{
    return (!complete.empty() && (getNextTask(Quality::passed) || getNextTask(Quality::redirect)));
}

void Processor::ship(OrderManager& finished){
    if (!complete.empty()){
    std::unique_ptr<CustomerOrder> order(new CustomerOrder(std::move(complete.front())));
    complete.pop_front();
    finished.emplace_back(std::move(*order));
    }
}
