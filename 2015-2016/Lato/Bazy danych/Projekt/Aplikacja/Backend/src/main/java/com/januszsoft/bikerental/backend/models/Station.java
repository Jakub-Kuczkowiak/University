package com.januszsoft.bikerental.backend.models;

import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
@Data
public class Station {

  @Id
  @GeneratedValue(strategy = GenerationType.AUTO)
  private Integer id;
  private Integer service;
  private String address;
  private Integer capacity;
  private Integer numberofreesapaces;
  private Double longitude;
  private Double latitude;
}
