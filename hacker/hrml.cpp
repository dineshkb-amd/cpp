#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

struct tagT{
	string tag_name; 
	vector< map<string, string>> attributes;
    struct tag *child, *sibling;
    struct tag *parent;
};

tagT *create_tag(string tag_name)
{
    tagT *tag = new (tagT);

    memset(tag, 0, sizeof(tagT));
    tag->tag_name = tag_name;
    return tag;
}

tagT *add_tag(tagT *tag, tagT *new_tag) 
{
    if (tag == NULL) {
        return new_tag;
    } else {
        new_tag->parent = tag;
        if (tag->child == NULL) {
            tag->child = new_tag;
        } else {
            tagT *child = tag->child;

            while (child->sibling != NULL);
            child->sibling = new_tag;
        }
    }

    return tag;
}

vector<string> &get_tokens(vector<string> &tokens)
{

}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int lines, queries;

    cin >> lines >> queries;

    for (int i = 0; i < lines; i++) {
	    getline(cin, line);

        string token;
        
        tagT* current_tag = NULL;
        tokens = get_tokens(line);

        while (getline (ss, token, ' ')) {
            if (token[0] == '<') { //new tag or closing tag
                if (token[1] = '/') {
                    tag_name = token.substr(2);
                    if (tag_name != current_tag.tag_name) {
                        printf ("Unwinding stack, tag not found\n");
                        exit(1);
                    } 

                    current_tag = current_tag->parent;
                } else { //Opening tag as a child
                    tag_name = token.substr(1);
                    current_tag = add_tag (current_tag, create_tag(tag_name));
                }
            } else {
                //attributes 
                string attribute = token; 



        }
    }
    return 0;
}
