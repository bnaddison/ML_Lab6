// ADDBRA001 ML Lab 5

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <memory>
#include <string>
#include <math.h>

using namespace std;

vector < pair<float,float> > node;

float node_output(vector< pair<float,float> > inputs) {
  float output = 0;
  for (int i = 0; i < inputs.size(); i++) {
    output += inputs[i].first*inputs[i].second;
  }

  //output+=bias;

  float o = sigmoid(output);

  return o;

}

float sigmoid (float net) {
  float o = 1/(1 + exp(-net) );
  return o;
}

float output_node_error(float o, float t) {
  float e = o*(1-o)*(t-o);
  return e;
}

float hidden_node_error(float o, vector< pair<float, float> > we ) {
  float error_sum = 0;
  for (int i = 0; i < we.size(); i++) {
    error_sum += we[i].first*we[i].second;
  }
  float e = o*(1-o)*error_sum;

  return e;
}

int main () {

  // input values
  float x1 = 0;
  float x2 = 1;

  // Initial connection weights
  float v11 = -1;
  float v21 = 0;
  float v12 = 0;
  float v22 = 1;

  float w11 = 1;
  float w21 = -1;
  float w12 = 0;
  float w22 = 1;

  pair <float, float> x1n1(x1,v11);
  pair <float, float> x1n2(x1,v21);

  pair <float, float> x2n1(x2,v12);
  pair <float, float> x2n2(x1,v22);

  node.push_back(x1n1);
  node.push_back(x2n1);
  float n1 = node_output(node);
  cout << n1 << endl;
  node.clear();

  node.push_back(x1n2);
  node.push_back(x2n2);
  float n2 = node_output(node);
  cout << n2 << endl;
  node.clear();

  pair <float, float> n1y1(n1,w11);
  pair <float, float> n1y2(n1,w21);

  pair <float, float> n2y1(n2,w12);
  pair <float, float> n2y2(n2,w22);

  node.push_back(n1y1);
  node.push_back(n2y1);
  float y1 = node_output(node);
  cout << y1 << endl;
  node.clear();

  node.push_back(n1y2);
  node.push_back(n2y2);
  float y2 = node_output(node);
  cout << y2 << endl;
  node.clear();




  return 0;
}
