/*
 * Bucket.inl.hpp
 *
 *  Created on: Nov 21, 2014
 *      Author: matheus
 */

#ifndef BUCKET_INL_HPP_
#define BUCKET_INL_HPP_

template <typename Vertex, typename Size>
BucketArray<Vertex, Size>::BucketArray() : buckets(new std::shared_ptr<std::list<Vertex>>[0]), total_vertices(0) {
  
}

template <typename Vertex, typename Size>
BucketArray<Vertex, Size>::~BucketArray() {
  delete[] buckets;
}

template <typename Vertex, typename Size>
void BucketArray<Vertex, Size>::init(Size size) {
  delete[] buckets;
  buckets = new std::shared_ptr<std::list<Vertex>>[size];
  for (Size i = 0; i < size; i++) {
    buckets[i].reset(new std::list<Vertex>);
  }
  total_vertices = 0;
}

template <typename Vertex, typename Size>
Size BucketArray<Vertex, Size>::size(Size i) const {
  return buckets[i]->size();
}

template <typename Vertex, typename Size>
bool BucketArray<Vertex, Size>::empty() const {
  return total_vertices == 0;
}

template <typename Vertex, typename Size>
Size BucketArray<Vertex, Size>::firstnonempty(Size current) const {
  while (buckets[current]->size() == 0) {
    current++;
  }
  return current;
}

template <typename Vertex, typename Size>
void BucketArray<Vertex, Size>::insert(Size i, Vertex v) {
  total_vertices++;
  buckets[i]->push_back(v);
}

template <typename Vertex, typename Size>
void BucketArray<Vertex, Size>::remove(Size i, Vertex v) {
  total_vertices--;
  buckets[i]->remove(v);
}

template <typename Vertex, typename Size>
std::shared_ptr<std::list<Vertex>> BucketArray<Vertex, Size>::pop(Size i) {
  total_vertices -= buckets[i]->size();
  std::shared_ptr<std::list<Vertex>> Q = buckets[i];
  buckets[i].reset(new std::list<Vertex>);
  return Q;
}

#endif /* BUCKET_INL_HPP_ */
