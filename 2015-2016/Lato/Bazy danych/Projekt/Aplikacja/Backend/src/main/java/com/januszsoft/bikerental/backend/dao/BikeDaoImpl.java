package com.januszsoft.bikerental.backend.dao;

import com.januszsoft.bikerental.backend.models.Bike;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;

import javax.sql.DataSource;
import java.util.List;

public class BikeDaoImpl implements Dao<Bike> {

  private JdbcTemplate jdbcTemplate;

  public BikeDaoImpl(DataSource dataSource) {
    jdbcTemplate = new JdbcTemplate(dataSource);
  }

  public void saveOrUpdate(Bike bike) {
    if (bike.getId() != null && bike.getId() > 0) {
      String sql = "UPDATE bike SET station=?, color=?, thelastoverviewdate=?, isingoodcondition=?, modelname=? WHERE id=?";

      jdbcTemplate.update(sql, bike.getStation(), bike.getColor(),
        bike.getThelastoverviewdate(), bike.getIsingoodcondition(), bike.getModelname(), bike.getId());
    }
    else {
      String sql = "INSERT INTO bike (station, color, thelastoverviewdate, isingoodcondition, modelname) VALUES (?, ?, ?, ?, ?)";
      jdbcTemplate.update(sql, bike.getStation(), bike.getColor(),
        bike.getThelastoverviewdate(), bike.getIsingoodcondition(), bike.getModelname());
    }
  }

  @Override
  public void delete(Integer bikeId) {
    String sql = "DELETE FROM bike WHERE id=?";
    jdbcTemplate.update(sql, bikeId);
  }

  @Override
  public Bike get(Integer bikeId) {

    String sql = "SELECT * FROM bike WHERE id=" + bikeId;
    List answer = jdbcTemplate.query(sql, new BeanPropertyRowMapper(Bike.class));
    if(answer.size() == 0) return null;
    else return (Bike) answer.get(0);

  }

  @Override
  public List<Bike> findall() {
    String sql = "SELECT * FROM bike";
    return jdbcTemplate.query(sql, new BeanPropertyRowMapper(Bike.class));
  }
}

