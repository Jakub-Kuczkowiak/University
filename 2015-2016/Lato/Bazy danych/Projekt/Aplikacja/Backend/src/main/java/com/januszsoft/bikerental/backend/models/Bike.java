package com.januszsoft.bikerental.backend.models;

import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import java.sql.Timestamp;

@Entity
@Data
public class Bike {

  @Id
  @GeneratedValue(strategy = GenerationType.AUTO)
  private Integer id;
  private Integer station;
  private String color;
  private Timestamp thelastoverviewdate;
  private Boolean isingoodcondition;
  private String modelname;
}
