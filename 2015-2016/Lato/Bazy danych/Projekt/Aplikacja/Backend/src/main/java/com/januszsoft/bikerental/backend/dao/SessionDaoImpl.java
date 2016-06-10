package com.januszsoft.bikerental.backend.dao;

import com.januszsoft.bikerental.backend.models.Issue;
import com.januszsoft.bikerental.backend.models.Session;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;

import javax.sql.DataSource;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.List;

public class SessionDaoImpl implements Dao<Session> {

  private JdbcTemplate jdbcTemplate;


  static String nextDayDate() {
    DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
    Calendar cal = Calendar.getInstance();
    cal.add(Calendar.DATE, 1);
    return dateFormat.format(cal.getTime());
  }

  public SessionDaoImpl(DataSource dataSource) {
    jdbcTemplate = new JdbcTemplate(dataSource);
  }

  public void saveOrUpdate(Session session) {
    if (session.getId() != null && session.getId() > 0) {
      String sql = "UPDATE session SET expiration_date=?, login=?, hash=? WHERE id=?";

      jdbcTemplate.update(sql, nextDayDate(), session.getLogin(), session.getHash(), session.getId());
    }
    else {
      String sql = "INSERT INTO session (expiration_date, login, hash) VALUES (?, ?, ?)";
      jdbcTemplate.update(sql, nextDayDate(), session.getLogin(), session.getHash());
    }
  }

  @Override
  public void delete(Integer sessionId) {
    String sql = "DELETE FROM session WHERE id=?";
    jdbcTemplate.update(sql, sessionId);
  }

  public void deleteWithHash(String hash) {
    String sql = "DELETE FROM session WHERE hash=\'?\'";
    jdbcTemplate.update(sql, hash);
  }

  @Override
  public Session get(Integer issueID) {

    String sql = "SELECT * FROM session WHERE id=" + issueID;
    List answer = jdbcTemplate.query(sql, new BeanPropertyRowMapper(Session.class));
    if(answer.size() == 0) return null;
    else return (Session) answer.get(0);
  }

  public Session getByHash(String cookiehash) {

    String sql = "SELECT * FROM session WHERE hash=\'" + cookiehash + "\'";
    List answer = jdbcTemplate.query(sql, new BeanPropertyRowMapper(Session.class));
    if(answer.size() == 0) return null;
    else return (Session) answer.get(0);

  }

  @Override
  public List<Session> findall() {
    String sql = "SELECT * FROM session";
    return jdbcTemplate.query(sql, new BeanPropertyRowMapper(Session.class));
  }
}

