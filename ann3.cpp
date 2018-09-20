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

float sigmoid (float net) {
  float o = 1/(1 + exp(-net) );
  return o;
}

float node_output(vector< pair<float,float> > inputs) {
  float output = 0;
  for (int i = 0; i < inputs.size(); i++) {
    output += inputs[i].first*inputs[i].second;
  }

  //output+=bias;

  float o = sigmoid(output);

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

  // target outputs
  float t1 = 1;
  float t2 = 0;

  // learning rate
  float n = 0.1f;


  pair <float, float> x1n1(x1,v11);
  pair <float, float> x1n2(x1,v21);

  pair <float, float> x2n1(x2,v12);
  pair <float, float> x2n2(x2,v22);

  node.push_back(x1n1);
  node.push_back(x2n1);
  float n1 = node_output(node);
  cout << "Hidden Node Output 1: " << n1 << endl;
  node.clear();

  node.push_back(x1n2);
  node.push_back(x2n2);
  float n2 = node_output(node);
  cout << "Hidden Node Output 2: " << n2 << endl;
  node.clear();

  pair <float, float> n1y1(n1,w11);
  pair <float, float> n1y2(n1,w21);

  pair <float, float> n2y1(n2,w12);
  pair <float, float> n2y2(n2,w22);

  node.push_back(n1y1);
  node.push_back(n2y1);
  float y1 = node_output(node);
  cout << "y1: " << y1 << endl;
  node.clear();

  node.push_back(n1y2);
  node.push_back(n2y2);
  float y2 = node_output(node);
  cout << "y2: " << y2 << endl;
  node.clear();

  float y1_error = output_node_error(y1,t1);
  float y2_error = output_node_error(y2,t2);
  cout << "y1 Error: " << y1_error << endl << "y2 Error: " << y2_error << endl;

  pair <float,float> w11y1e(w11,y1_error);
  pair <float,float> w21y2e(w21,y2_error);
  pair <float,float> w12y1e(w12,y1_error);
  pair <float,float> w22y2e(w22,y2_error);
  node.push_back(w11y1e);
  node.push_back(w21y2e);
  //node.push_back(w12y1e);
  //node.push_back(w22y2e);
  float n1_error = hidden_node_error(n1, node);
  node.clear();

  node.push_back(w12y1e);
  node.push_back(w22y2e);
  float n2_error = hidden_node_error(n2, node);
  node.clear();

  w11+= n*y1_error*n1;
  w21+= n*y2_error*n1;
  w12+= n*y1_error*n2;
  w22+= n*y2_error*n2;
  cout << "w11: " << w11 << endl << "w21: " << w21 << endl << "w12: " << w12 << endl << "w22: " << w22 << endl;

  cout << "Hidden Node 1 Error: " << n1_error << endl << "Hidden Node 2 Error: " << n2_error << endl;

  v11+= n*n1_error*x1;
  v21+= n*n2_error*x1;
  v12+= n*n1_error*x2;
  v22+= n*n2_error*x2;

  cout << "v11: " << v11 << endl << "v21: " << v21 << endl <<  "v12: " << v12 << endl << "v22: " << v22 << endl;


  //float n1_error = hidden_node_error()


  return 0;
}
