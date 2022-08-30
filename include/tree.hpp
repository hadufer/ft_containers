#pragma once
#include "iterator.hpp"
#include "utils.hpp"
#include "pair.hpp"

namespace ft {
	template<class T>
	struct Node{
	public:
		T		mValue;
		Node*	mParent;
		Node*	mLeft;
		Node*	mRight;
		bool	mBlack;

	Node(const T &value = 0, Node* parentArg = NULL, Node* leftArg = NULL, Node* rightArg = NULL, bool blackArg = false) :	mValue(value), mParent(parentArg), mLeft(leftArg), mRight(rightArg), mBlack(blackArg) {}
	Node(Node* parentArg = NULL, Node* leftArg = NULL, Node* rightArg = NULL, bool blackArg = false) : mParent(parentArg), mLeft(leftArg), mRight(rightArg), mBlack(blackArg) {}
	};

	template <class data, class T>
	class TreeIterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef T								node;
			typedef data&							reference;
			typedef data*							pointer;
		private:
			node*	mRootPtr;
			node*	mActualPtr;
			node*	mLastPtr;
			node*	mMidPtr;

		public:
			TreeIterator() : mRootPtr(NULL), mActualPtr(NULL),  mLastPtr(NULL), mMidPtr(NULL) {}
			TreeIterator(node* actualPtr, node* rootPtr, node* lastPtr, node* midPtr = NULL) : mRootPtr(rootPtr), mActualPtr(actualPtr),  mLastPtr(lastPtr), mMidPtr(midPtr) {}
			TreeIterator(const TreeIterator &cpy) : mRootPtr(cpy.mRootPtr), mActualPtr(cpy.mActualPtr), mLastPtr(cpy.mLastPtr), mMidPtr(cpy.mMidPtr) {}

			TreeIterator &operator++()
			{
				node* tmpNodePtr = mActualPtr;
				node* tmpIncNodePtr = NULL;
				if (tmpNodePtr->mRight == mLastPtr)
				{
					if (!mMidPtr)
					{
						tmpIncNodePtr = tmpNodePtr->mParent;
						while ((tmpIncNodePtr != mLastPtr) && (tmpNodePtr == tmpIncNodePtr->mRight))
						{
							tmpNodePtr = tmpIncNodePtr;
							tmpIncNodePtr = tmpIncNodePtr->mParent;
						}
					}
					else
						return (*this);
				}
				else
				{
					if (!mMidPtr)
					{
						tmpIncNodePtr = tmpNodePtr->mRight;
						while (tmpIncNodePtr->mLeft != mLastPtr)
							tmpIncNodePtr = tmpIncNodePtr->mLeft;
					}
					else
						return (*this);
				}
				mActualPtr = tmpIncNodePtr;
				return (*this);
			}

			TreeIterator operator++(int)
			{
				TreeIterator tmp(*this);
				operator++();
				return (tmp);
			}

			TreeIterator &operator--()
			{
				node* tmpNodePtr = mRootPtr;
				node* tmpPrevPtr = NULL;
				if (mActualPtr == mLastPtr)
				{
					if (mMidPtr)
					{
						operator--();
						return (*this);
					}
					else
					{
						while (tmpNodePtr->mRight != mLastPtr)
							tmpNodePtr = tmpNodePtr->mRight;
						mActualPtr = tmpNodePtr;
						return *this;
					}
				}
				else
				{
					if ((mMidPtr == mLastPtr) && (mActualPtr == mMidPtr))
						return (*this);
					else
					{
						tmpNodePtr = mActualPtr;
						if (tmpNodePtr->mLeft == mLastPtr)
						{
							tmpPrevPtr = tmpNodePtr->mParent;
							while (tmpPrevPtr != mLastPtr && tmpNodePtr == tmpPrevPtr->mLeft)
							{
								tmpNodePtr = tmpPrevPtr;
								tmpPrevPtr = tmpPrevPtr->mParent;
							}
							mActualPtr = tmpPrevPtr;
							return *this;
						}
						else
						{
							tmpNodePtr = tmpNodePtr->mLeft;
							while (tmpNodePtr->mRight != mLastPtr)
								tmpNodePtr = tmpNodePtr->mRight;
							mActualPtr = tmpNodePtr;
							return *this;
						}
					}
				}
			}

			TreeIterator operator--(int)
			{
				TreeIterator tmp(*this);
				operator--();
				return (tmp);
			}

			operator TreeIterator<const data, T>() const { return TreeIterator<const data, T>(mActualPtr, mRootPtr, mLastPtr);}
			bool operator==(const TreeIterator &iterator) const { return mActualPtr == iterator.mActualPtr;}
			bool operator!=(const TreeIterator &iterator) const { return mActualPtr != iterator.mActualPtr; }
			reference operator*() { return mActualPtr->mValue;}
			reference operator*() const { return mActualPtr->mValue; }
			pointer operator->() const { return &mActualPtr->mValue; }
			node* base() const { return mActualPtr; }
	};

	template <class data, class T1, class T2>
	bool operator==(const TreeIterator<data, T1> &lhs, const TreeIterator<data, T2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class data, class T1, class T2>
	bool operator!=(const TreeIterator<data, T1> &lhs, const TreeIterator<data, T2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class T, class Compare, class Allocator = std::allocator<Node<T> > >
	class Tree {
		public:
			typedef T												value_type;
			typedef size_t											size_type;
			typedef Node<value_type>								node;
			typedef ft::TreeIterator<value_type, node>				iterator;
			typedef ft::TreeIterator<const value_type, node>		const_iterator;
			typedef std::reverse_iterator<iterator>					reverse_iterator;
			typedef std::reverse_iterator<const_iterator>			const_reverse_iterator;
		private:
			node*													mRootNodePtr;
			node*													mLastPtr;
			size_type												mSize;
			Allocator												mAllocator;
			Compare													mCompare;
		public:
			Tree() : mSize(0), mAllocator(Allocator()), mCompare(Compare())
			{
				node *tmpNodePtr = mAllocator.allocate(1);
				mAllocator.construct(tmpNodePtr, Node<value_type>(tmpNodePtr, tmpNodePtr, tmpNodePtr, true));
				mLastPtr = tmpNodePtr;
				mRootNodePtr = tmpNodePtr;
			}

			Tree(const Tree &cpy) : mSize(cpy.mSize), mAllocator(cpy.mAllocator), mCompare(cpy.mCompare)
			{
				node *tmpNodePtr = mAllocator.allocate(1);
				mAllocator.construct(tmpNodePtr, Node<value_type>(tmpNodePtr, tmpNodePtr, tmpNodePtr, true));
				mLastPtr = tmpNodePtr;
				mRootNodePtr = tmpNodePtr;
				recursiveCopy((*this), cpy.mRootNodePtr, cpy.mLastPtr, NULL);
			}

			~Tree()
			{
				recursiveClear(mRootNodePtr);
				mAllocator.deallocate(mLastPtr, 1);
			}

			Tree	&operator=(const Tree &cpy)
			{
				clear();
				recursiveCopy((*this), cpy.mRootNodePtr, cpy.mLastPtr, NULL);
				return (*this);
			}

			void clear()
			{
				recursiveClear(mRootNodePtr);
				mSize = (size_type)NULL;
				mRootNodePtr = mLastPtr;
			}

			ft::pair<iterator, bool> insert(const value_type &value)
			{
				node* newNodePtr = mAllocator.allocate(1);
				node* tmpNodePtr = NULL;
				node* tmpNewNodePtr = newNodePtr;
				mAllocator.construct(newNodePtr, value);
				newNodePtr->mBlack = false;
				newNodePtr->mLeft = mLastPtr;
				newNodePtr->mRight = mLastPtr;
				newNodePtr->mParent = mLastPtr;
				int outInsert = 0;
				node* insertedNodePtr = recursiveInsert(mRootNodePtr, newNodePtr, outInsert);
				if (!outInsert)
				{
					mAllocator.destroy(newNodePtr);
					mAllocator.deallocate(newNodePtr, 1);
					return (ft::make_pair(iterator(insertedNodePtr, mRootNodePtr, mLastPtr), outInsert));
				}
				else
				{
					mSize++;
					if (newNodePtr->mParent == mLastPtr)
					{
						newNodePtr->mBlack = outInsert;
					}
					else
					{
						while (tmpNewNodePtr->mParent->mBlack != outInsert)
						{
							if (tmpNewNodePtr->mParent == tmpNewNodePtr->mParent->mParent->mRight)
							{
								tmpNodePtr = tmpNewNodePtr->mParent->mParent->mLeft;
								if (tmpNodePtr->mBlack != outInsert)
								{
									tmpNodePtr->mBlack = outInsert;
									tmpNewNodePtr->mParent->mBlack = outInsert;
									tmpNewNodePtr->mParent->mParent->mBlack = !outInsert;
									tmpNewNodePtr = tmpNewNodePtr->mParent->mParent;
								}
								else
								{
									if (tmpNewNodePtr == tmpNewNodePtr->mParent->mLeft)
									{
										tmpNewNodePtr = tmpNewNodePtr->mParent;
										rightRotate(tmpNewNodePtr);
									}
									tmpNewNodePtr->mParent->mBlack = outInsert;
									tmpNewNodePtr->mParent->mParent->mBlack = !outInsert;
									leftRotate(tmpNewNodePtr->mParent->mParent);
								}
							}
							else
							{
								tmpNodePtr = tmpNewNodePtr->mParent->mParent->mRight;

								if (tmpNodePtr->mBlack == !outInsert)
								{
									tmpNodePtr->mBlack = outInsert;
									tmpNewNodePtr->mParent->mBlack = outInsert;
									tmpNewNodePtr->mParent->mParent->mBlack = !outInsert;
									tmpNewNodePtr = tmpNewNodePtr->mParent->mParent;
								}
								else
								{
									if (tmpNewNodePtr == tmpNewNodePtr->mParent->mRight)
									{
										tmpNewNodePtr = tmpNewNodePtr->mParent;
										leftRotate(tmpNewNodePtr);
									}
									tmpNewNodePtr->mParent->mBlack = outInsert;
									tmpNewNodePtr->mParent->mParent->mBlack = !outInsert;
									rightRotate(tmpNewNodePtr->mParent->mParent);
								}
							}
							if (tmpNewNodePtr == mRootNodePtr)
								break;
						}
						mRootNodePtr->mBlack = outInsert;
					}
					tmpNodePtr = newNodePtr;
					while (tmpNodePtr->mParent != mLastPtr)
						tmpNodePtr = tmpNodePtr->mParent;
					mRootNodePtr = tmpNodePtr;
					return (ft::make_pair(iterator(newNodePtr, mRootNodePtr, mLastPtr), outInsert));
				}
			}

			iterator insert(iterator ite, const value_type &value)
			{
				node* beginNodePtr = ite.base();
				node* tmpNodePtr = mLastPtr;
				node* next = NULL;
				node* minNodePtr = beginNodePtr->mRight;

				if (beginNodePtr->mRight != mLastPtr)
				{
					while (minNodePtr->mLeft != mLastPtr)
						minNodePtr = minNodePtr->mLeft;
					next = minNodePtr;
				}
				tmpNodePtr = beginNodePtr->mParent;
				while (tmpNodePtr != mLastPtr && beginNodePtr == tmpNodePtr->mRight)
				{
					beginNodePtr = tmpNodePtr;
					tmpNodePtr = tmpNodePtr->mParent;
				}
				next = tmpNodePtr;
				if (mCompare(value, next->mValue) && mCompare(ite.base()->mValue, value))
				{
					node* newNodePtr = mAllocator.allocate(1);
					mAllocator.construct(newNodePtr, value);
					newNodePtr->mBlack = false;
					newNodePtr->mLeft = mLastPtr;
					newNodePtr->mRight = mLastPtr;
					newNodePtr->mParent = mLastPtr;
					int outInsert = 0;
					node* insertedNodePtr = recursiveInsert(ite.base(), newNodePtr, outInsert, NULL);
					mSize++;
					return (iterator(insertedNodePtr, mRootNodePtr, mLastPtr));
				}
				else
					return (insert(value).first);
			}

			void erase(iterator ite)
			{
				node *nodeToErase = ite.base();
				node *tmpNodeErase = ite.base();
				node *memNode = NULL;
				node *tmpNodePtr = NULL;

				if (ite.base() != mLastPtr)
				{
					bool yIsBlack = tmpNodeErase->mBlack;

					if (nodeToErase->mLeft == mLastPtr || nodeToErase->mRight == mLastPtr)
					{
						if (nodeToErase->mRight == mLastPtr)
						{
							memNode = nodeToErase->mLeft;
							invertNode(nodeToErase, nodeToErase->mLeft);
						}
						else if (nodeToErase->mLeft == mLastPtr)
						{
							memNode = nodeToErase->mRight;
							invertNode(nodeToErase, nodeToErase->mRight);
						}
					}
					else
					{
						tmpNodePtr = nodeToErase->mRight;
						while (tmpNodePtr->mLeft != mLastPtr)
							tmpNodePtr = tmpNodePtr->mLeft;
						tmpNodeErase = tmpNodePtr;
						yIsBlack = tmpNodeErase->mBlack;
						memNode = tmpNodeErase->mRight;
						
						if (tmpNodeErase->mParent != nodeToErase)
						{
							invertNode(tmpNodeErase, tmpNodeErase->mRight);
							tmpNodeErase->mRight = nodeToErase->mRight;
							tmpNodeErase->mRight->mParent = tmpNodeErase;
						}
						else
							memNode->mParent = tmpNodeErase;
						invertNode(nodeToErase, tmpNodeErase);
						tmpNodeErase->mLeft = nodeToErase->mLeft;
						tmpNodeErase->mLeft->mParent = tmpNodeErase;
						tmpNodeErase->mBlack = nodeToErase->mBlack;
					}
					mAllocator.destroy(nodeToErase);
					mAllocator.deallocate(nodeToErase, 1);
					mSize--;
					if (yIsBlack)
						removeFixTree(memNode);
				}
			}
 
			size_type erase(value_type const &toErase)
			{
				node* nodeToErase = searchNode(toErase);
				node* tmpNodeToErase = searchNode(toErase);
				node* memNode = NULL;
				node *tmpNodePtr = NULL;

				if (!searchNode(toErase))
					return (size_type)NULL;
				else
				{
					bool yIsBlack = tmpNodeToErase->mBlack;

					if (nodeToErase->mLeft == mLastPtr || nodeToErase->mRight == mLastPtr)
					{
						if (nodeToErase->mLeft == mLastPtr)
						{
							memNode = nodeToErase->mRight;
							invertNode(nodeToErase, nodeToErase->mRight);
						}
						else if (nodeToErase->mRight == mLastPtr)
						{
							memNode = nodeToErase->mLeft;
							invertNode(nodeToErase, nodeToErase->mLeft);
						}
					}
					else
					{
						tmpNodePtr = nodeToErase->mRight;
						while (tmpNodePtr->mLeft != mLastPtr)
							tmpNodePtr = tmpNodePtr->mLeft;
						tmpNodeToErase = tmpNodePtr;
						yIsBlack = tmpNodeToErase->mBlack;
						memNode = tmpNodeToErase->mRight;
						if (tmpNodeToErase->mParent == nodeToErase)
							memNode->mParent = tmpNodeToErase;
						else
						{
							invertNode(tmpNodeToErase, tmpNodeToErase->mRight);
							tmpNodeToErase->mRight = nodeToErase->mRight;
							tmpNodeToErase->mRight->mParent = tmpNodeToErase;
						}
						invertNode(nodeToErase, tmpNodeToErase);
						tmpNodeToErase->mLeft = nodeToErase->mLeft;
						tmpNodeToErase->mLeft->mParent = tmpNodeToErase;
						tmpNodeToErase->mBlack = nodeToErase->mBlack;
					}
					mAllocator.destroy(nodeToErase);
					mAllocator.deallocate(nodeToErase, 1);
					mSize--;
					if (!yIsBlack)
						return (size_type)1;
					else
					{
						removeFixTree(memNode);
						return (size_type)1;
					}
				}
			}

			iterator find(const value_type &valueToFind)
			{
				if (searchNode(valueToFind))
					return iterator(searchNode(valueToFind), mRootNodePtr, mLastPtr, NULL);
				else
					return ((iterator)end());
			}

			const_iterator find(const value_type &valueToFind) const
			{
				if (searchNode(valueToFind))
					return const_iterator(searchNode(valueToFind), mRootNodePtr, mLastPtr, NULL);
				else
					return ((const_iterator)end());
			}

			void swap(Tree &toSwap)
			{
				node*	tmpRootNodePtr = toSwap.mRootNodePtr;
				node*	tmpNil = toSwap.mLastPtr;
				size_type	tmpSize = toSwap.mSize;
				Allocator	tmpAllocator = toSwap.mAllocator;
				Compare		tmpCompare = toSwap.mCompare;

				toSwap.mRootNodePtr = mRootNodePtr;
				toSwap.mLastPtr = mLastPtr;
				toSwap.mSize = mSize;
				toSwap.mAllocator = mAllocator;
				toSwap.mCompare = mCompare;
				mRootNodePtr = tmpRootNodePtr;
				mLastPtr = tmpNil;
				mAllocator = tmpAllocator;
				mSize = tmpSize;
				mCompare = tmpCompare;
			}

			iterator begin()
			{
				node *tmpNodePtr = mRootNodePtr;
				while (tmpNodePtr->mLeft != mLastPtr)
					tmpNodePtr = tmpNodePtr->mLeft;
				return iterator(tmpNodePtr, mRootNodePtr, mLastPtr, NULL);
			}

			const_iterator begin() const
			{
				node *tmpNodePtr = mRootNodePtr;
				while (tmpNodePtr->mLeft != mLastPtr)
					tmpNodePtr = tmpNodePtr->mLeft;
				return const_iterator(tmpNodePtr, mRootNodePtr, mLastPtr, NULL);
			}

			iterator end() { return iterator(mLastPtr, mRootNodePtr, mLastPtr, NULL); }
			const_iterator end() const { return const_iterator(mLastPtr, mRootNodePtr, mLastPtr, NULL); }
			reverse_iterator rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
			size_type size() const { return (mSize);}
			size_type max_size() const { return (mAllocator.max_size()); }

			private:

			void recursiveClear(node *nodePtr)
			{
				if (nodePtr->mRight != mLastPtr)
					recursiveClear(nodePtr->mRight);
				if (nodePtr->mLeft != mLastPtr)
					recursiveClear(nodePtr->mLeft);
				if (nodePtr != mLastPtr)
				{
					mAllocator.destroy(nodePtr);
					mAllocator.deallocate(nodePtr, 1);
				}
			}

			void recursiveCopy(Tree &newTree, node *rootNodePtr, node *lastPtr, node *stopNodePtr = NULL)
			{
				if (rootNodePtr != lastPtr || rootNodePtr == stopNodePtr)
				{
					recursiveCopy(newTree, rootNodePtr->mRight, lastPtr, stopNodePtr);
					newTree.insert(rootNodePtr->mValue);
					recursiveCopy(newTree, rootNodePtr->mLeft, lastPtr, stopNodePtr);
				}
			}

			node* recursiveInsert(node *rootNodePtr, node *nodePtr, int &outInsert, node *stopNodePtr = NULL)
			{
				if (rootNodePtr != mLastPtr || rootNodePtr == stopNodePtr)
				{
					if (mCompare(rootNodePtr->mValue, nodePtr->mValue))
					{
						if (rootNodePtr->mRight == mLastPtr)
							rootNodePtr->mRight = nodePtr;
						else
							return (recursiveInsert(rootNodePtr->mRight, nodePtr, outInsert, stopNodePtr));
					}
					else if (mCompare(nodePtr->mValue, rootNodePtr->mValue))
					{
						if (rootNodePtr->mLeft == mLastPtr)
							rootNodePtr->mLeft = nodePtr;
						else
							return (recursiveInsert(rootNodePtr->mLeft, nodePtr, outInsert, stopNodePtr));
					}
					else
					{
						outInsert = 0;
						return (rootNodePtr);
					}
				}
				nodePtr->mParent = rootNodePtr;
				nodePtr->mBlack = false;
				nodePtr->mLeft = mLastPtr;
				nodePtr->mRight = mLastPtr;
				outInsert = 1;
				return (nodePtr);
			}

			void leftRotate(node *toRotate)
			{
				node* tmpNodePtr = toRotate->mRight;
				toRotate->mRight = tmpNodePtr->mLeft;
				if (tmpNodePtr->mLeft != mLastPtr)
					tmpNodePtr->mLeft->mParent = toRotate;
				tmpNodePtr->mParent = toRotate->mParent;
				if (toRotate->mParent == mLastPtr)
					this->mRootNodePtr = tmpNodePtr;
				else if (toRotate == toRotate->mParent->mLeft)
					toRotate->mParent->mLeft = tmpNodePtr;
				else
					toRotate->mParent->mRight = tmpNodePtr;
				tmpNodePtr->mLeft = toRotate;
				toRotate->mParent = tmpNodePtr;
			}

			void rightRotate(node *toRotate)
			{
				node* tmpNodePtr = toRotate->mLeft;
				toRotate->mLeft = tmpNodePtr->mRight;
				if (tmpNodePtr->mRight != mLastPtr)
					tmpNodePtr->mRight->mParent = toRotate;
				tmpNodePtr->mParent = toRotate->mParent;
				if (toRotate->mParent == mLastPtr)
					this->mRootNodePtr = tmpNodePtr;
				else if (toRotate == toRotate->mParent->mRight)
					toRotate->mParent->mRight = tmpNodePtr;
				else
					toRotate->mParent->mLeft = tmpNodePtr;
				tmpNodePtr->mRight = toRotate;
				toRotate->mParent = tmpNodePtr;
			}

			void removeFixTree(node* nodeToErase)
			{
				node* tmpNodeToErase = NULL;
				while (nodeToErase != mRootNodePtr && nodeToErase->mBlack)
				{
					if (nodeToErase != nodeToErase->mParent->mLeft)
					{
						tmpNodeToErase = nodeToErase->mParent->mLeft;
						if (tmpNodeToErase->mBlack == false)
						{
							tmpNodeToErase->mBlack = true;
							nodeToErase->mParent->mBlack = false;
							rightRotate(nodeToErase->mParent);
							tmpNodeToErase = nodeToErase->mParent->mLeft;
						}
						if (tmpNodeToErase->mRight->mBlack == false || tmpNodeToErase->mLeft->mBlack == false)
						{
							if (tmpNodeToErase->mLeft->mBlack == true)
							{
								tmpNodeToErase->mRight->mBlack = true;
								tmpNodeToErase->mBlack = false;
								leftRotate(tmpNodeToErase);
								tmpNodeToErase = nodeToErase->mParent->mLeft;
							}
							tmpNodeToErase->mBlack = nodeToErase->mParent->mBlack;
							nodeToErase->mParent->mBlack = true;
							tmpNodeToErase->mLeft->mBlack = true;
							rightRotate(nodeToErase->mParent);
							nodeToErase = mRootNodePtr;
						}
						else
						{
							tmpNodeToErase->mBlack = false;
							nodeToErase = nodeToErase->mParent;
						}
					}
					else
					{
						tmpNodeToErase = nodeToErase->mParent->mRight;
						if (tmpNodeToErase->mBlack == false)
						{
							tmpNodeToErase->mBlack = true;
							nodeToErase->mParent->mBlack = false;
							leftRotate(nodeToErase->mParent);
							tmpNodeToErase = nodeToErase->mParent->mRight;
						}
						if (tmpNodeToErase->mRight->mBlack == false || tmpNodeToErase->mLeft->mBlack == false)
						{
							if (tmpNodeToErase->mRight->mBlack)
							{
								tmpNodeToErase->mLeft->mBlack = true;
								tmpNodeToErase->mBlack = false;
								rightRotate(tmpNodeToErase);
								tmpNodeToErase = nodeToErase->mParent->mRight;
							}
							tmpNodeToErase->mBlack = nodeToErase->mParent->mBlack;
							nodeToErase->mParent->mBlack = true;
							tmpNodeToErase->mRight->mBlack = true;
							leftRotate(nodeToErase->mParent);
							nodeToErase = mRootNodePtr;
						}
						else
						{
							tmpNodeToErase->mBlack = false;
							nodeToErase = nodeToErase->mParent;
						}
					}
					
				}
				nodeToErase->mBlack = true;
			}

			void invertNode(node* oldNodePtr, node* currNodePtr)
			{
				if (oldNodePtr == oldNodePtr->mParent->mLeft)
					oldNodePtr->mParent->mLeft = currNodePtr;
				else if (oldNodePtr->mParent == mLastPtr)
					mRootNodePtr = currNodePtr;
				else
					oldNodePtr->mParent->mRight = currNodePtr;
				currNodePtr->mParent = oldNodePtr->mParent;
			}

			node* searchNode(value_type const &value) const
			{
				node* tmpNodePtr = mRootNodePtr;
				while (tmpNodePtr != mLastPtr)
				{
					if (!mCompare(value, tmpNodePtr->mValue) && !mCompare(tmpNodePtr->mValue, value))
						return (tmpNodePtr);
					else
					{
						if (mCompare(value, tmpNodePtr->mValue))
							tmpNodePtr = tmpNodePtr->mLeft;
						else if (mCompare(tmpNodePtr->mValue, value))
							tmpNodePtr = tmpNodePtr->mRight;
					}
				}
				return ((node*)NULL);
			}
	};

}