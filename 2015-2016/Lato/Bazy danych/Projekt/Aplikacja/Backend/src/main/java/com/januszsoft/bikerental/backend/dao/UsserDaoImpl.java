package com.januszsoft.bikerental.backend.dao;

import com.januszsoft.bikerental.backend.models.Usser;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;

import javax.sql.DataSource;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.List;

public class UsserDaoImpl implements Dao<Usser> {

  private JdbcTemplate jdbcTemplate;


  public UsserDaoImpl(DataSource dataSource) {
    jdbcTemplate = new JdbcTemplate(dataSource);
  }

  public void saveOrUpdate(Usser usser) {
    if ( usser.getId() != null && usser.getId() > 0) {
      String sql = "UPDATE usser SET name=?, surname=?, address=?, pesel=?," +
        "email=?, phonenumber=?, balance=?, bike=?, passwordhash=? WHERE id=?";

      jdbcTemplate.update(sql, usser.getName(), usser.getSurname(),
        usser.getAddress(), usser.getPesel(), usser.getEmail(),
        usser.getPhonenumber(), usser.getBalance(), usser.getBike(), usser.getPasswordhash(), usser.getId());
    }
    else {

      String sql_count = "SELECT COUNT (*) FROM usser";
      int numberOfUssers = jdbcTemplate.queryForObject(sql_count, Integer.class);

      String sql = "INSERT INTO usser (id, name, surname, address, pesel, email, phonenumber, balance, bike, passwordhash) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
      jdbcTemplate.update(sql, numberOfUssers+1, usser.getName(), usser.getSurname(),
        usser.getAddress(), usser.getPesel(), usser.getEmail(),
        usser.getPhonenumber(), usser.getBalance(), usser.getBike(), usser.getPasswordhash());
    }
  }

  @Override
  public void delete(Integer usserId) {
    String sql = "DELETE FROM usser WHERE id=?";
    jdbcTemplate.update(sql, usserId);
  }

  @Override
  public Usser get(Integer usserId) {

    String sql = "SELECT * FROM usser WHERE id=" + usserId;
    List answer = jdbcTemplate.query(sql, new BeanPropertyRowMapper(Usser.class));
    if(answer.size() == 0) return null;
    else return (Usser) answer.get(0);

  }

  public Usser getUserByPesel(String pesel) {

    String sql = "SELECT * FROM usser WHERE pesel=\'" + pesel + "\'";
    List answer = jdbcTemplate.query(sql, new BeanPropertyRowMapper(Usser.class));
    if(answer.size() == 0) return null;
    else return (Usser) answer.get(0);

  }

  @Override
  public List<Usser> findall() {
    String sql = "SELECT * FROM usser";
    return jdbcTemplate.query(sql, new BeanPropertyRowMapper(Usser.class));
  }
}

