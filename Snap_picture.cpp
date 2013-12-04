/* Snap_picture.cpp
 * Group: Chris Findeisen, Martin Fracker, Daniel Frazee
 * Keeps track of the filename of a picture and its tags
 */

#include "Snap_picture.h"

const int Snap_picture::MAX_TAGS = 5;

void Snap_picture::add_tag(string s) {
	if (tags.size() < MAX_TAGS) {
		tags.push_back(s);
	}
}