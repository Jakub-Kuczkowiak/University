package com.januszsoft.bikerental.backend.models;

import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import java.sql.Timestamp;

@Entity
@Data
public class Session {
  @Id
  @GeneratedValue(strategy = GenerationType.AUTO)
  private Integer id;
  private String expiration_date;
  private String login;
  private String hash;
}

