package com.januszsoft.bikerental.backend.dao;

import java.util.List;

public interface Dao <E> {
    public void saveOrUpdate(E object);
    public void delete(Integer objectId);
    public E get(Integer objectId);
    public List<E> findall();
}

