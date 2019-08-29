#include <iostream>
#include "json.hpp"

#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(max_size + 1, KeyValuePair()),
	max_size_(max_size),
	size_(0) {
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));

}

void PriorityQueue::insert(KeyValuePair kv) {
    size_ +=1;
    nodes_[size_] = kv;
    heapifyUp(size_);
}

KeyValuePair PriorityQueue::min() {
    return nodes_[1];
}

KeyValuePair PriorityQueue::removeMin() {
    KeyValuePair temp = nodes_[1];
    //nodes_[1] = nodes_[size_];  //sets root equal to last node of heap.

    //nodes_.erase(nodes_.begin() + size_); //removes the last node of heap.
    removeNode(1);
    //size_ -=1;
    //heapifyDown(1)  ;
    return temp;
}

bool PriorityQueue::isEmpty() const {
	if (nodes_.empty())
	{
		return true;
	}
	return false;
}

size_t PriorityQueue::size() const {
			return size_;

}

nlohmann::json PriorityQueue::JSON() const {
	nlohmann::json result;
  for (size_t i = 1; i <= size_; i++) {
      nlohmann::json node;
      KeyValuePair kv = nodes_[i];
      node["key"] = kv.first;
      node["value"] = kv.second;
      if (i != ROOT) {
          node["parent"] = std::to_string(i / 2);
      }
      if (2 * i <= size_) {
          node["leftChild"] = std::to_string(2 * i);
      }
      if (2 * i + 1 <= size_) {
          node["rightChild"] = std::to_string(2 * i + 1);
      }
      result[std::to_string(i)] = node;
  }
  result["metadata"]["maxHeapSize"] = max_size_;
  result["metadata"]["max_size"] = max_size_;

  result["metadata"]["size"] = size_;
	return result;
}

void PriorityQueue::heapifyUp(size_t i)

{
		// check if node at index i and its parent violates
		// the heap property
		if (i && nodes_[i/2].first > nodes_[i].first)
		{
			// swap the two if heap property is violated
			swap(nodes_[i], nodes_[i/2]);

			// call Heapify-up on the parent
			heapifyUp(i/2);
		}

}

void PriorityQueue::heapifyDown(size_t i) {
		// get left and right child of node at index i
		size_t left = 2*i;
		size_t right = 2*i+1;

		size_t smallest = i;

		// compare A[i] with its left and right child
		// and find smallest value
		if (left <= size_ && nodes_[left].first < nodes_[i].first)
        {


			smallest = left;
        }
		if (right <= size_ && nodes_[right].first < nodes_[smallest].first)
        {


			smallest = right;
        }
		// swap with child having lesser value and
		// call heapify-down on the child
		if (smallest != i) {
			swap(nodes_[i], nodes_[smallest]);
			heapifyDown(smallest);
		}

}

void PriorityQueue::removeNode(size_t i) {
    nodes_[i] = nodes_[size_];  //sets ith node equal to last node of heap.
    nodes_.erase(nodes_.begin() + size_); //removes the last node of heap.
    size_ -=1;
    if (nodes_[i].first < nodes_[i/2].first)
    {
        heapifyUp(i);
    }
    else
    {
        heapifyDown(i);
    }

}

Key PriorityQueue::getKey(size_t i) {
	return nodes_[i].first;
}


void PriorityQueue::remove_team(Value v)
{
    for (int i = 1; i <= size_; i ++)
    {
        int player1 = nodes_[i].second.first;
        int player2 = nodes_[i].second.second;
        if ((v.first == player1) || (v.second == player2) || (v.first == player2) || (v.second == player1) )
        {
            removeNode(i);
            remove_team(v);
        }
    }

}


