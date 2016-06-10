package com.januszsoft.bikerental.backend.dao;

import com.januszsoft.bikerental.backend.models.Rent;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;

import javax.sql.DataSource;
import java.util.List;

public class RentDaoImpl implements Dao<Rent> {

  private JdbcTemplate jdbcTemplate;

  public RentDaoImpl(DataSource dataSource) {
    jdbcTemplate = new JdbcTemplate(dataSource);
  }

  public void saveOrUpdate(Rent rent) {
    if (rent.getId() != null && rent.getId() > 0) {
      String sql = "UPDATE rent SET bike=?, usser=?, startdate=?, enddate=? WHERE id=?";

      jdbcTemplate.update(sql, rent.getBike(), rent.getUsser(),
        rent.getStartdate(), rent.getEnddate(), rent.getId());
    }
    else {
      String sql = "INSERT INTO rent (bike, usser, startdate, enddate) VALUES (?, ?, ?, ?)";
      jdbcTemplate.update(sql, rent.getBike(), rent.getUsser(),
        rent.getStartdate(), rent.getEnddate());
    }
  }

  @Override
  public void delete(Integer rentID) {
    String sql = "DELETE FROM rent WHERE id=?";
    jdbcTemplate.update(sql, rentID);
  }

  @Override
  public Rent get(Integer rentID) {

    String sql = "SELECT * FROM rent WHERE id=" + rentID;
    List answer = jdbcTemplate.query(sql, new BeanPropertyRowMapper(Rent.class));
    if(answer.size() == 0) return null;
    else return (Rent) answer.get(0);
  }

  public Rent lastRentForGivenBike(Integer bikeid) {

    String sql = "SELECT * FROM rent WHERE bike=" + bikeid +" ORDER BY startdate DESC LIMIT 1";
    List answer = jdbcTemplate.query(sql, new BeanPropertyRowMapper(Rent.class));
    if(answer.size() == 0) return null;
    else return (Rent) answer.get(0);
  }

  @Override
  public List<Rent> findall() {
    String sql = "SELECT * FROM rent";
    return jdbcTemplate.query(sql, new BeanPropertyRowMapper(Rent.class));
  }
}

