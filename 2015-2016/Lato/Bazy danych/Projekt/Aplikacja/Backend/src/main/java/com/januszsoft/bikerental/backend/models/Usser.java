package com.januszsoft.bikerental.backend.models;

import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
@Data
public class Usser {

  @Id
  @GeneratedValue(strategy = GenerationType.AUTO)
  private Integer id;
  private String name;
  private String surname;
  private String address;
  private String pesel;
  private String email;
  private Double balance;
  private String phonenumber;
  private String passwordhash;
  private Integer bike;
}
