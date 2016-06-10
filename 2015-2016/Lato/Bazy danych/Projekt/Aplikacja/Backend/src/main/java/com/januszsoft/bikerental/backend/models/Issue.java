package com.januszsoft.bikerental.backend.models;

import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import java.sql.Timestamp;

@Entity
@Data
public class Issue {

  @Id
  @GeneratedValue(strategy = GenerationType.AUTO)
  private Integer id;
  private Integer reportedbyusser;
  private Integer bike;
  private Timestamp reportdate;
  private Timestamp finishdate;
  private String description;

}
