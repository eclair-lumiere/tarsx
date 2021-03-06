
#include "BindAdapter.h"
#include "EpollServer.h"

using namespace tarsx;

BindAdapter::BindAdapter(EpollServer* epoll_server) {
	epollServer_ = epoll_server;
}

BindAdapter::~BindAdapter() {
	//epollServer_->terminate();
}

auto BindAdapter::insertRecvDeque(std::deque<utagRecvData>& deque, bool pushback) -> void {
	if(pushback) {
		receiveBuffer_.push_back(deque);
	}
	else {
		receiveBuffer_.push_front(deque);
	}
	if(auto handleGroup=handleGroup_.lock()) {
		Lock lock(handleGroup->monitor);
		handleGroup->monitor.notify();
	}
}

auto BindAdapter::waitForRecvQueue(uint32_t wait_time) -> utagRecvData {
	return receiveBuffer_.pop_front(wait_time);
}
