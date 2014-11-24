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
    std::shared_ptr<std::list<Vertex>>* buckets;
    Size total_vertices;
  public:
    BucketArray();
    ~BucketArray();
    void init(Size size);
    Size totalvertices() const;
    Size size(Size i) const;
    Size firstnonempty(Size current) const;
    void insert(Size i, Vertex v);
    void remove(Size i, Vertex v);
    std::shared_ptr<std::list<Vertex>> pop(Size i);
  private:
    inline Size getindex(Size j) const;
};

#include "Bucket.inl.hpp"

#endif /* BUCKET_HPP_ */
