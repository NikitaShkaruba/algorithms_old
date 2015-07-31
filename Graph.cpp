//#include "Graph.h"
//
//namespace algo {
//		Edge::Edge(Edge& edge): from_(edge.from_), to_(edge.to_) {}
//		Edge::Edge(Node* from, Node* to) : from_(from), to_(to) {}
//		Edge::Edge() : from_(nullptr), to_(nullptr) {} 
//		Edge::~Edge() {
//			from_->tear(to_);
//			to_->tear(from_);
//		}
//		bool Edge::operator==(const Edge& pretendent)  {
//			if (this->from_ == pretendent.from_ && this->to_ == pretendent.to_ || this->from_ == pretendent.to_&& this->to_ == pretendent.from_)
//				return true;
//			else 
//				return false;
//		}
//		//Edge& Edge::operator=(const Edge& other) {
//		//	from_->tear(to_);
//		//	to_->tear(from_);
//		//	return *this;
//		//}
//		bool Edge::isSelfLoop() {
//			return from_ == to_;
//		}
//		void Edge::fuse() {
//			from_->merge(to_);
//		}
//
//		Node::Node(Node* nodesToConnect, size_t nodeCount) : edges_() {
//			for(size_t i = 0; i < nodeCount; i++)
//				this->attach(&nodesToConnect[i]);	
//		}
//		Node::Node() : edges_() {}
//		Node::~Node() {
//			for (auto i = edges_.begin(); i != edges_.end(); i++)
//				delete *i;
//		}
//		Edge* Node::attach(Node* neighbour) {
//			Edge* edge = new Edge(this, neighbour);
//			
//			neighbour->edges_.push_back(edge);
//			this->edges_.push_back(edge);
//
//			return edge;
//		}
//		void Node::merge(Node* node) {
//			int* a = new int(2);
//			delete a;
//
//			for(auto i = node->edges_.begin(); i != node->edges_.end(); i++) {
//				if ((*i)->from_ == node)
//					(*i)->from_ = this;
//				else 
//					(*i)->to_ = this;
//
//				edges_.push_back(*i);
//			}
//			node->edges_.clear();
//			//delete node;
//		}
//		void Node::tear(Node* node) {
//			for(auto i = edges_.begin(); i < edges_.end(); i++) 
//				if ((*i)->from_ == node || (*i)->to_ == node) {
//					edges_.erase(i);
//					return;
//				}
//			throw "This node have not this edge.";
//		}
//		Node* Node::go(Edge* edge) const  {
//			if (edge->from_ == this || edge->to_ == this)
//				return edge->from_ == this? edge->to_ : edge->from_;	
//			else 
//				throw "This node don't have this edge";
//		}
//		void Node::removeSelfLoops() {
//			for(auto i = edges_.begin(); i != edges_.end(); i++) {
//				if ((*i)->isSelfLoop()) {
//					edges_.erase(i);
//					delete *i;
//				}
//			}
//		}
//		bool Node::isConnected(Node* node) {
//			for(auto i = node->edges_.begin(); i != node->edges_.end(); i++)
//				if ((*i)->from_ == node || (*i)->to_ == node)
//					return true;
//			return false;
//		}
//
//		Graph::Graph(Node* nodes, Edge* edges, size_t nodeCount, size_t edgeCount) : nodes_(nodes), edges_(edges), nCount(nodeCount), eCount(edgeCount) {}
//		Graph::Graph(const Graph& graph) {
//			nCount = graph.nCount;
//			eCount = graph.eCount;
//			
//			nodes_ = new Node[nCount];
//			for(size_t i = 0; i < nCount; i++)
//				nodes_[i] = graph.nodes_[i];
//			edges_ = new Edge[eCount];
//			for(size_t i = 0; i < nCount; i++)
//				edges_[i] = graph.edges_[i];
//		}
//		Graph::~Graph() {
//			delete edges_;	// O(m)
//			delete nodes_;	// O(n)
//		}
//		Graph& Graph::operator=(const Graph& other) {
//			Graph tmp(other);
//			this->swap(tmp);
//			return *this;
//		}
//		void Graph::swap(Graph& other) {
//			Edge* buf = edges_;
//			edges_ = other.edges_;
//			other.edges_ = buf;
//
//			Node* buf2 = nodes_;
//			nodes_ = other.nodes_;
//			other.nodes_ = buf2;
//
//			int buf3 = eCount;
//			eCount = other.eCount;
//			other.eCount = buf3;
//
//			int buf4 = nCount;
//			nCount = other.nCount;
//			other.nCount = buf4;
//		}
//		void Graph::fuseEdge(Edge* edge) {
//			edge->fuse();
//
//		}
//		Node* Graph::getNodes() {
//			return nodes_;
//		}
//		Edge* Graph::getEdges() {
//			return edges_;
//		}
//		size_t Graph::getNodesCount() {
//			return nCount;
//		}
//		size_t Graph::getEdgesCount() {
//			return eCount;
//		}
//}