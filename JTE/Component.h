#pragma once
#include <vector>
#include <queue>

namespace JTL
{
	namespace SIM
	{
		template<typename T>
		struct Handle
		{
			int idx;
			Handle(int i = -1) : idx(i), dataref(&Component<T>::getData()) {}

			T *operator->()		  { return &Component<T>::at(idx); }
			T *operator->() const { return &Component<T>::at(idx); }
			T  operator* () const { return  Component<T>::at(idx); }
			T &operator* ()		  { return  Component<T>::at(idx); }
			T *operator& ()		  { return &Component<T>::at(idx); }
			
			operator int ()		  { return idx; }
			operator int () const { return idx; }

		private:
			std::vector<T> *dataref;
		};

		template<typename T>
		class Component
		{
			int idx;
			bool isVacant;

			static std::queue<int> &getQueue() { static std::queue<int> q; return q; }
		
		public:

			static std::vector<T> &getData() { static std::vector<T> d; return d; }

			static T &at(int i) { return getData()[i]; }

			static void free(int i)
			{
				if (i > -1 && !at(i).isVacant)
				{
					at(i).onFree();
					getQueue().push(i);
					at(i).isVacant = true;
					at(i).idx = -1;
				}
			}

			static Handle<T> make()
			{
				int i = -1;

				if (getQueue().size() > 0)
				{
					i = getQueue().front();
					getQueue().pop();
					at(i) = T();
				}
				else
				{
					i = getData().size();
					getData().emplace_back();
				}

				at(i).idx = i;
				at(i).isVacant = false;

				return Handle<T>{i};
			}

			int			 getIndex() { return idx; }
			bool		 isValid () { return !isVacant; }
			virtual void onFree	 () {}
		};
	}
}