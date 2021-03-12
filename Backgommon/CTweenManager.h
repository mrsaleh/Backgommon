#pragma once

#include <vector>
#include <array>
#include <stdexcept>
#include "tween.hpp"

enum struct Easing
{
	Linear,

	QuadIn,          // t^2
	QuadOut,
	QuadInOut,
	CubicIn,         // t^3
	CubicOut,
	CubicInOut,
	QuartIn,         // t^4
	QuartOut,
	QuartInOut,
	QuintIn,         // t^5
	QuintOut,
	QuintInOut,
	SineIn,          // sin(t)
	SineOut,
	SineInOut,
	ExpoIn,          // 2^t
	ExpoOut,
	ExpoInOut,
	CircIn,          // sqrt(1-t^2)
	CircOut,
	CircInOut,
	ElasticIn,       // exponentially decaying sine wave
	ElasticOut,
	ElasticInOut,
	BackIn,          // overshooting cubic easing: (s+1)*t^3 - s*t^2
	BackOut,
	BackInOut,
	BounceIn,        // exponentially decaying parabolic bounce
	BounceOut,
	BounceInOut,

	SineSquare,      // gapjumper's
	Exponential,     // gapjumper's
	Schubring1,      // terry schubring's formula 1
	Schubring2,      // terry schubring's formula 2
	Schubring3,      // terry schubring's formula 3

	SinPI2,          // tomas cepeda's
	Swing,           // tomas cepeda's & lquery's

	Total,
	Undefined
};

template<typename T>
class TSharedRef {
private:
	T& _mValue;
public:
	TSharedRef(T& v) :_mValue(v) {}
	T& GetValue() {
		return _mValue;
	}
};

template <typename T,size_t Size >
class CTween {
private:
	float passedTime;
	float duration;
	bool finished;
	TSharedRef<std::array <T, Size>> startValue;
	std::array<T, Size> endValue;
	std::array<T, Size> value;
	Easing easing;

public:
	CTween(TSharedRef<std::array <T,Size>> start, std::array<T, Size> end,Easing easing) {
		finished = false;
		value = startValue = start;
		endValue = end;
		this->easing = easing;
	}

	void Update(float deltaTime) {
		if (finished)
			throw std::runtime_error("Error in the TweenManager, it is still updating a finished tween!");
		passedTime += deltaTime;
		if (passedTime) {
			float time = passedTime / duration;
			if (time > 1) {
				time = 1;
				finished = true;
				float timeEasing = tween::cubicinout(time);
				
				for (
					auto itStartValue = startValue.GetValue().begin(),
					itEndValue = endValue.begin(),
					itValue = value.begin();
					itStartValue != startValue.end();
					itStartValue++, itEndValue++, itValue++
					) {
					(*itValue) = (1 - timeEasing) * (*itStartValue) + timeEasing * (*itEndValue);
				}
				
			}			
		}		
	}

	bool Finished() {
		return finished;
	}

	T getValue() {
		return value;
	}
	
};

typedef CTween<float,1> CTweenFloat ;
typedef CTween<float, 2> CTweenFloat2;
typedef CTween<float, 3> CTweenFloat3;




class CTweenManager
{
public:
	void Goto(float &x,float &y,float targetX,float targetY,Easing easing) {
		Get().NewTween2(x, y, targetX, targetY,easing);
	}

private:
	static CTweenManager& Get() {
		static CTweenManager instance;
		return instance;
	}
private:
	std::vector<CTweenFloat2*> tweens;
private:
	void NewTween2(TSharedRef<float> startX, TSharedRef<float> startY, float endX,float endY, Easing easing) {
		CTweenFloat2* newTween = new CTweenFloat2(;
		tweens.push_back()
	}

	void Update(float deltaTime) {
		std::vector<std::vector<CTweenFloat2*>::const_iterator> finishedTweens;
		for (auto it = tweens.begin(); it != tweens.end();it++) {
			CTweenFloat2* tween = (*it);
			

			tween->Update(deltaTime);
			if (tween->Finished()) {
				finishedTweens.push_back(it);
			}
		}
		//Removes finished tweens
		for (auto it = finishedTweens.begin(); it != finishedTweens.end(); it++) {			
			tweens.erase(*it);
		}
	}	
};

