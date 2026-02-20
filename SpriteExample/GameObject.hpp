#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

class GameObject {
	public:
		GameObject() {}
		virtual ~GameObject() {};

		// All of these dont not neccesarily need an override, say some GameObjects have no visuals
		virtual void init() {} // Runs when the GameObject is pushed to Scene vector
		virtual void update() {} // Runs once per update of the Scene
		virtual void draw() {} // Runs once per frame update of the Scene
		virtual void onDestruction() {} // Runs at the end of a frame after destroy in Scene update

		bool isAlive() const { return isAlive_; }
		void destroy() { isAlive_ = false; } // Call this function or just change isAlive to delete GameObject

	private:
		bool isAlive_;
};

#endif