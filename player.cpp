#include"player.h"
#include"actor.h"
#include"stack.h"
#include"list.h"
#include"point.h"
#include"aquarium.h"
#include<iostream>

//  Player( ... )
//		Constructs and initializes the Player/Actor and its member variables
//		Remembers and discovers the starting point.
Player::Player(Aquarium* aquarium, Point p, std::string name, char sprite):Actor(aquarium, p, name, sprite),
	m_look(),
	m_discovered(),
	m_btQueue(),
	m_btStack(),
	m_toggleBackTracking(false) {

	// Discover the starting point
	m_discovered.push_front(p);
	m_look.push(p);
}

//  stuck() 
//		See if the player is stuck in the maze (no solution)
bool Player::stuck() const {
	return Actor::getState() == State::STUCK;
}

//  foundExit()
//		See if the player has found the exit
bool Player::foundExit() const {
	return Actor::getState() == State::FREEDOM;
}
//  toggleBackTrack( ... )
//		Turn on/off backtracking
void Player::toggleBackTrack(bool toggle) {
	m_toggleBackTracking = toggle;
}

//  getTargetPoint()
//		Get the point the player wants to look around next.
//      If m_look is empty then return an invalid point.
Point Player::getTargetPoint() const {
	if (m_look.empty()) return Point(-1, -1);
	return m_look.peek();
}

// discovered
//		returns true if the item is in the list
bool Player::discovered(const Point &p) const {
	return (m_discovered.find(p) != -1);
}



// say()
//		What does the player say?
//		Already Implemented, nothing to do here
void Player::say() {

	// Freedom supercedes being eaten
	if (getState() == State::FREEDOM) {
		std::cout << getName() << ": WEEEEEEEEE!";
		return;
	} 
 
	// Being eaten supercedes being lost
	switch (getInteract()) {
	case Interact::ATTACK:
		std::cout << getName() << ": OUCH!";
		break;
	case Interact::GREET:
		break;
	case Interact::ALONE:
	default:
		switch (getState()) {
		case State::LOOKING:
			std::cout << getName() << ": Where is the exit?";
			break;
		case State::STUCK:
			std::cout << getName() << ": Oh no! I am Trapped!";
			break;
		case State::BACKTRACK:
			std::cout << getName() << ": Got to backtrack...";
			break;
		default:
			break;
		}

		break;
	}
}


//  update() 
//		This function implements an algorithm to look through the maze
//      for places to move (STATE::LOOKING). update also handles moving the 
//		player as well, if there is an open undiscovered cell to move to the  
//		player just moves there.  However, there will be cases in the next 
//		desired point to look around is not adjacent (more than one cell away), 
//		at this point the player must backtrack (State::BACKTRACK) to a point 
//		that is adjacent to the next point the player was planning to visit
//

void Player::update() {
	m_look.pop();

	Point p = getPosition();
	int x = p.getX();
	int y = p.getY();
	cout << "start: " << p.getX() << " " << p.getY() << endl;

	while (p != (getAquarium()->getEndPoint())) {
		p.set(x - 1, y - 1);

		if (getAquarium()->isCellOpen(p)) {
			p.set(x - 1, y - 1); m_discovered.push_front(p); m_look.push(p); break;
		}

		else {
			p.set(x + 1, y + 1);

			if (getAquarium()->isCellOpen(p)) {
				p.set(x - 1, y - 1); m_discovered.push_front(p); m_look.push(p); break;
			}

			else {
				p.set(x, y - 1);

				if (getAquarium()->isCellOpen(p)) {

					p.set(x, y - 1); m_discovered.push_front(p); m_look.push(p); break;
				}

				else
				{
					p.set(x, y + 1);

					if (getAquarium()->isCellOpen(p)) {
						p.set(x, y + 1); m_discovered.push_front(p); m_look.push(p); break;
					}

					else
						return;
				}

			}

			return;


		}




		/*	}

		/
			if (!getAquarium()->isCellOpen(p))
				return;

			setPosition(p);*/



			/*
			//m_look.pop();
			while (p != (getAquarium()->getEndPoint())) {

				p.set(x - 1, y - 1);

				if (!getAquarium()->isCellOpen(p))
					return;
				else
					m_discovered.push_front(p);
					m_look.push(p);



				/*
					if ((x - 1, y - 1) == ' '){
						p.set(x - 1, y - 1);
						if (!m_discovered.find(p)) {
							x--; y--;

							m_discovered.push_front(p);
							m_look.push(p);
							break;
						}
						else
							return;

					}

					else if ((x + 1, y + 1) == ' ') {

						if (!m_discovered.find(p)) {
							//x++; y++;
							cout << p.getX() << " " << p.getY() << endl;
							p.set(x + 1, y + 1);
							m_discovered.push_front(p);
							m_look.push(p);
							break;
							}
						else
							return;


					}

					else if ((x, y - 1) == ' ') {

						if (!m_discovered.find(p)) {
							// y--;
							p.set(x, y - 1);
							m_discovered.push_front(p);
							m_look.push(p);
							break;
						}

						else
							return;


					}

					else if ((x, y + 1) == ' ') {
						if (!m_discovered.find(p)) {
							//y++;
							p.set(x, y + 1);
							m_discovered.push_front(p);
							m_look.push(p);
							break;
						}
						else
							return;


					}

				}

				return;

			}*/

			// Set by the settings file and checked here
			// if(m_toggleBackTracking) { ... code relating to backtracking 

	}


}
