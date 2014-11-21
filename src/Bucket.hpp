/*
 * Bucket.hpp
 *
 *  Created on: Nov 21, 2014
 *      Author: matheus
 */

#ifndef BUCKET_HPP_
#define BUCKET_HPP_

#include <list>

template <typename Vertex = int, typename Size = int>
class BucketArray {
  private:
    Size size_;
    std::list<Vertex>* buckets;
    Size total_vertices;
  public:
    BucketArray();
    ~BucketArray();
    void init(Size size);
    Size size() const;
    Size size(Size i) const;
    bool empty() const;
    Size firstnonempty(Size current) const;
    void insert(Size i, Vertex v);
    void remove(Size i, Vertex v);
    std::list<Vertex> clear(Size i);
};

#include "Bucket.inl.hpp"

#endif /* BUCKET_HPP_ */
