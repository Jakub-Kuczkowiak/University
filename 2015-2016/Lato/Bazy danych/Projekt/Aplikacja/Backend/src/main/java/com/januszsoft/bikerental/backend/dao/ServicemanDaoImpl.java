package com.januszsoft.bikerental.backend.dao;

import com.januszsoft.bikerental.backend.models.Serviceman;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;

import javax.sql.DataSource;
import java.util.List;

public class ServicemanDaoImpl implements Dao<Serviceman> {

  private JdbcTemplate jdbcTemplate;

  public ServicemanDaoImpl(DataSource dataSource) {
    jdbcTemplate = new JdbcTemplate(dataSource);
  }

  public void saveOrUpdate(Serviceman serviceman) {
    if ( serviceman.getId() != null && serviceman.getId() > 0) {
      String sql = "UPDATE serviceman SET name=?, surname=?, email=?, phonenumber=? WHERE id=?";

      jdbcTemplate.update(sql, serviceman.getName(), serviceman.getSurname(),
        serviceman.getEmail(), serviceman.getPhonenumber(), serviceman.getId());
    }
    else {
      String sql = "INSERT INTO serviceman (name, surname, email, phonenumber) VALUES (?, ?, ?, ?)";
      jdbcTemplate.update(sql, serviceman.getName(), serviceman.getSurname(),
        serviceman.getEmail(), serviceman.getPhonenumber());
    }
  }

  @Override
  public void delete(Integer servicemanID) {
    String sql = "DELETE FROM serviceman WHERE id=?";
    jdbcTemplate.update(sql, servicemanID);
  }

  @Override
  public Serviceman get(Integer servicemanID) {

    String sql = "SELECT * FROM serviceman WHERE id=" + servicemanID;
    List answer = jdbcTemplate.query(sql, new BeanPropertyRowMapper(Serviceman.class));
    if(answer.size() == 0) return null;
    else return (Serviceman) answer.get(0);

  }

  @Override
  public List<Serviceman> findall() {
    String sql = "SELECT * FROM serviceman";
    return jdbcTemplate.query(sql, new BeanPropertyRowMapper(Serviceman.class));
  }
}

