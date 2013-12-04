/* Snap_picture.h
 * Group: Chris Findeisen, Martin Fracker, Daniel Frazee
 * Keeps track of the filename of a picture and its tags
 */

#ifndef SNAP_PICTURE_DEFINED // include guard
#define SNAP_PICTURE_DEFINED

#include "Snap_facilities.h"

// this class does not hold an actual binary
// it holds a filename and tags
class Snap_picture {
public:
	Snap_picture(string fname) :filename(fname) {  }
	
	// add up to 5 tags (see Snap_picture::Max_tags)
	void add_tag(string s);
	
	// public getters
	string get_filename() const { return filename; }
	string get_tag(int i) const { return tags[i]; } // access each individual tag
	int get_tag_count() const { return tags.size(); } // how many tags there currently are
	vector<string> get_tags() const { return tags; } // sometimes we need access to its iterators
	
	// static constant: maximum number of tags
	static const int MAX_TAGS;
private:
	string filename;
	vector<string> tags;
};

#endif // SNAP_PICTURE_DEFINED