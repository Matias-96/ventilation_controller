/*
 * Imutex.hpp
 *
 *  Created on: 21.9.2023
 *      Author: jpj1
 */

#ifndef IMUTEX_HPP_
#define IMUTEX_HPP_

class Imutex {
public:
 Imutex();
 ~Imutex();
 void lock();
 void unlock();
private:
 bool enable;
};


#endif /* IMUTEX_HPP_ */
