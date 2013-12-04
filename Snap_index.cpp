/* Snap_index.cpp
 * Group: Chris Findeisen, Martin Fracker, Daniel Frazee
 * Keeps track of Snap_picture objects via an index file
 */

#include <boost/filesystem.hpp>
#include "Snap_facilities.h"
#include "Snap_index.h"
#include "Snap_picture.h"
#include "Snap_util.h"

const char Snap_index::SEPARATOR = '/';
const string Snap_index::NO_TAG = "%nt%";

// find a picture with the given filename
Snap_picture Snap_index::find_by_filename(string fname) {
	for (auto pic : pictures)
		if (pic.get_filename() == fname)
			return pic;
	throw Invalid_filename();
}

int Snap_index::get_index_of(const Snap_picture& pic) {
	// this works all the time because we already made sure that filenames are unique
	for (int i = 0; i < pictures.size(); ++i)
		if (pictures[i].get_filename() == pic.get_filename())
			return i;
	return pictures.size();
}

void Snap_index::remove_picture(int i) {
	string path = Snap::image_dir + pictures[i].get_filename();
	boost::filesystem::remove(path);
	pictures.erase(pictures.begin() + i);
	rebuild_index();
}

void Snap_index::rebuild_index() {
	boost::filesystem::remove(filename);
	for (auto pic : pictures) {
		save_picture(pic);
	}
}

// write pic info to index file and add it to pictures vector
void Snap_index::save_picture(const Snap_picture& pic) {
	add_picture(pic);
	ofstream ofs;
	ofs.open(filename, ios::app); // append to the existing index file
	if (!ofs) return;
	ofs << pic.get_filename(); // add a line to the index in the format: fname / tag1 / ... / tag5
	for (int i = 0; i < pic.get_tag_count(); ++i)
		ofs << ' ' << SEPARATOR << ' ' << pic.get_tag(i);
	for (int i = 0; i < Snap_picture::MAX_TAGS-pic.get_tag_count(); ++i)
		ofs << ' ' << SEPARATOR << ' ' << NO_TAG; // use "no tag" tokens if there were less than 5 tags
	ofs << endl;
}

// parse the index file into Snap_picture objects
void Snap_index::parse_index() {
	string fname; // filename for current picture
	vector<string> tags(Snap_picture::MAX_TAGS);
	Snap_picture* current; // pointer to the current picture
    char ch1, ch2, ch3, ch4, ch5;
	ifstream ifs(filename);
	int i = 0;
	while (ifs) {
		ifs >> fname >> ch1 >> tags[0] >> ch2 >> tags[1] >> ch3 >> tags[2] >> ch4 >> tags[3] >> ch5 >> tags[4]; // read a line
		if ((ch1 != SEPARATOR || ch2 != SEPARATOR || ch3 != SEPARATOR || ch4 != SEPARATOR || ch5 != SEPARATOR) || !ifs) { // format error or EOF
			if (ifs.eof()) break;
			ifs.clear(ios_base::failbit);
			throw Bad_format();
		}
		add_picture(fname); // instantiate the current picture object with the filename we just read
		current = &pictures[i];
		for (int j = 0; j < tags.size(); ++j)
			if (tags[j] != NO_TAG) // some pictures won't have five tags
				current->add_tag(tags[j]);
		++i;
	}
}

void Snap_index::add_picture(const Snap_picture& pic) {
	// pre-condition so that rebuild_index() won't cause infinite loop
	if (!Snap::duplicate_filename(pic.get_filename(), false)) pictures.push_back(pic);
}

vector<Snap_picture> Snap_index::find_all_with_tags(vector<string> tags) {
	sort(tags.begin(), tags.end()); // this is why tags is not passed by reference; copy assignment would happen either way
	vector<string> check;
	vector<Snap_picture> result;
	for (auto pic:pictures) {
		check = pic.get_tags();
		sort(check.begin(), check.end());
		if (includes(check.begin(), check.end(), tags.begin(), tags.end()))
			result.push_back(pic);
	}
	return result;
}